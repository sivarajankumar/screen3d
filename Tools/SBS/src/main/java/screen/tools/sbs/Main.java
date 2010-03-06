package screen.tools.sbs;

import java.io.File;
import java.util.List;

import org.w3c.dom.Document;

import screen.tools.sbs.cmake.SBSCMakeFileGenerator;
import screen.tools.sbs.cmake.SBSCMakeLauncher;
import screen.tools.sbs.objects.Dependency;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.Flag;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.FieldString;
import screen.tools.sbs.utils.Logger;
import screen.tools.sbs.utils.OptionHandler;
import screen.tools.sbs.utils.OptionHandler.Phase;
import screen.tools.sbs.xml.SBSDomDataFiller;
import screen.tools.sbs.xml.SBSDomParser;

public class Main {
	private static void checkFields(Pack pack){
		Logger.info("pack = " + pack.getProperties().getName().getString());
		Logger.info("version = " + pack.getProperties().getVersion().getString());
		Logger.info("build = " + pack.getProperties().getBuildType().getString());
		
		List<Dependency> deps = pack.getDependencyList();
		for (int i=0; i<deps.size(); i++){
			Logger.info("Dependency{");
			
			Dependency dep = deps.get(i);
			Logger.info("    name = " + dep.getName().getString());
			Logger.info("    root dir = " + dep.getRoot().getString());
			Logger.info("    is SBS dependency = " + dep.getSbs().getString());
			
			List<FieldPath> incs = dep.getIncludePathList();
			for(int j=0; j<incs.size(); j++){
				Logger.info("    include path = " + incs.get(j).getString());
			}
			
			List<FieldPath> libPaths = dep.getLibraryPathList();
			for(int j=0; j<libPaths.size(); j++){
				Logger.info("    library path = " + libPaths.get(j).getString());
			}
			
			List<FieldString> libs = dep.getLibraryNameList();
			for(int j=0; j<libs.size(); j++){
				Logger.info("    library name = " + libs.get(j).getString());
			}
			
			Logger.info("}");
		}
		
		List<Flag> flags = pack.getFlagList();
		for (int i=0; i<flags.size(); i++){
			Logger.info("Flag{");
			Logger.info("    flag = "+flags.get(i).getFlag().getString());
			Logger.info("    value = "+flags.get(i).getValue().getString());
			Logger.info("    config = "+flags.get(i).getConfig().getString());
			Logger.info("}");
		}
	}
	
	private static boolean checkErrors(){
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		if(err.hasErrors()){
			Logger.info("errors detected");
			Logger.info("Logged errors (" + err.getErrors().size() + ") :");
			err.displayErrors();
			if(err.hasWarnings()){
				Logger.info("Logged warnings (" + err.getWarnings().size() + ")");
				err.displayWarnings();
			}
			Logger.info("============== STOP ===============");
			return false;
		}else if(err.hasWarnings()){
			Logger.warning("warnings detected");
			Logger.info("Logged warnings (" + err.getWarnings().size() + ")");
			err.displayWarnings();
		}
		return true;
	}
	
	public static void main(String[] args) throws Exception {
		Logger.info("------------ begin SBS ------------");
		
		Logger.info("----- begin parse parameters ------");
		OptionHandler optHandler = new OptionHandler(args);
		if(!checkErrors()){
			optHandler.usage();
			return;
		}
		Logger.info("------ end parse parameters -------");
		
		List<Phase> phaseList = optHandler.getPhaseList();
		Pack pack = new Pack();
		
		for(int i=0; i<phaseList.size(); i++){
			Phase phase = phaseList.get(i);
			
			if(phase == Phase.LOAD_CONF){
				Logger.info("---- begin load configuration -----");
				String root = System.getProperty("SBS_ROOT");
				GlobalSettings.getGlobalSettings().getEnvironmentVariables().putFromFile(root+"/sbs.config");
				if(!checkErrors()) return;
				Logger.info("----- end load configuration ------");
			}
			else if(phase == Phase.LOAD_XML){
				Logger.info("-------- begin XML parsing --------");
				Document doc = SBSDomParser.parserFile(new File(optHandler.getSbsXmlPath()+"sbs.xml"));
				if(!checkErrors()) return;
				Logger.info("--------- end XML parsing ---------");
				
				Logger.info("--------- begin data fill ---------");
				SBSDomDataFiller dataFiller = new SBSDomDataFiller(pack);
				dataFiller.fill(doc);
				if(!checkErrors()) return;
				Logger.info("---------- end data fill ----------");
			}
			else if(phase == Phase.CHECK){
				Logger.info("------- begin check fields --------");
				checkFields(pack);
				if(!checkErrors()) return;
				Logger.info("-------- end check fields ---------");
			}
			else if(phase == Phase.GENERATE){
				Logger.info("----- begin generate makefile -----");
				SBSCMakeFileGenerator generator = new SBSCMakeFileGenerator(pack, optHandler.getSbsXmlPath());
				generator.generate();
				if(!checkErrors()) return;
				SBSCMakeLauncher launcher = new SBSCMakeLauncher();
				launcher.launch(optHandler.getSbsXmlPath());
				if(!checkErrors()) return;
				Logger.info("------ end generate makefile ------");
			}
			else if(phase == Phase.COMPILE){
				Logger.info("-------- begin compilation --------");
				Logger.warning("TODO");
				Logger.info("--------- end compilation ---------");
			}
			else if(phase == Phase.TEST){
				Logger.info("----------- begin test ------------");
				Logger.warning("TODO");
				Logger.info("------------ end test -------------");
				
			}
		}
		
		Logger.info("------------- end SBS -------------");
	}
}
