package screen.tools.sbs;

import java.io.File;
import java.util.List;

import org.w3c.dom.Document;

import screen.tools.sbs.cmake.SBSCMakeCleaner;
import screen.tools.sbs.cmake.SBSCMakeFileGenerator;
import screen.tools.sbs.cmake.SBSCMakeLauncher;
import screen.tools.sbs.objects.Dependency;
import screen.tools.sbs.objects.Description;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.Flag;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.objects.Library;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.Logger;
import screen.tools.sbs.utils.OptionHandler;
import screen.tools.sbs.utils.OptionHandler.Phase;
import screen.tools.sbs.xml.SBSDomDataFiller;
import screen.tools.sbs.xml.SBSDomParser;

public class Main {
	private static void checkFields(Pack pack){
		Logger.info("Properties :");
		Logger.info("pack = " + pack.getProperties().getName().getString());
		Logger.info("version = " + pack.getProperties().getVersion().getString());
		Logger.info("build = " + pack.getProperties().getBuildType().getString());
		
		Logger.info("Dependencies :");
		List<Dependency> deps = pack.getDependencyList();
		for (int i=0; i<deps.size(); i++){
			Logger.info("Dependency{");
			
			Dependency dep = deps.get(i);
			if(!dep.getName().isEmpty())
				Logger.info("    name = " + dep.getName().getString());
			if(!dep.getVersion().isEmpty())
				Logger.info("    version = " + dep.getVersion().getString());
			
			List<FieldPath> incs = dep.getIncludePathList();
			for(int j=0; j<incs.size(); j++){
				Logger.info("    include path = " + incs.get(j).getString());
			}
			
			List<FieldPath> libPaths = dep.getLibraryPathList();
			for(int j=0; j<libPaths.size(); j++){
				Logger.info("    library path = " + libPaths.get(j).getString());
			}
			
			List<Library> libs = dep.getLibraryList();
			for(int j=0; j<libs.size(); j++){
				if(!libs.get(j).getName().isEmpty())
					Logger.info("    library name = " + libs.get(j).getName().getString());
				if(!libs.get(j).getVersion().isEmpty())
					Logger.info("    library version = " + libs.get(j).getVersion().getString());
			}
			
			Logger.info("}");
		}
		
		Logger.info("Flags :");
		List<Flag> flags = pack.getFlagList();
		for (int i=0; i<flags.size(); i++){
			Logger.info("Flag{");
			Logger.info("    flag = "+flags.get(i).getFlag().getString());
			Logger.info("    value = "+flags.get(i).getValue().getString());
			Logger.info("}");
		}
		
		Logger.info("Descriptions :");
		List<Description> descs = pack.getDescriptionList();
		for (int i=0; i<descs.size(); i++){
			Logger.info("Description{");
			Logger.info("    name = "+descs.get(i).getName().getString());
			Logger.info("    compileName = "+descs.get(i).getCompileName().getString());
			Logger.info("    fullName = "+descs.get(i).getFullName().getString());
			Logger.info("    buildType = "+descs.get(i).getBuildType());
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
		Pack testPack = new Pack();
		SBSDomDataFiller dataFiller = null;
		Document doc = null;
		
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
				doc = SBSDomParser.parserFile(new File(optHandler.getSbsXmlPath()+optHandler.getSbsXmlFile()));
				if(!checkErrors()) return;
				Logger.info("--------- end XML parsing ---------");
				
				Logger.info("--------- begin data fill ---------");
				dataFiller = new SBSDomDataFiller(pack,testPack,new FieldPath(optHandler.getSbsXmlPath()));
				dataFiller.fill(doc,false);
				if(!checkErrors()) return;
				Logger.info("---------- end data fill ----------");
			}
			else if(phase == Phase.CHECK){
				Logger.info("------- begin check fields --------");
				checkFields(pack);
				if(!checkErrors()) return;
				Logger.info("-------- end check fields ---------");
			}
			else if(phase == Phase.DEPLOY_HEADER){
				Logger.info("---- begin deploy header files ----");
				SBSHeaderDeployer deployer = new SBSHeaderDeployer();
				deployer.deploy(optHandler.getSbsXmlPath(), pack);
				Logger.info("----- end deploy header files -----");
			}
			else if(phase == Phase.GENERATE){
				Logger.info("----- begin generate makefile -----");
				SBSCMakeFileGenerator generator = new SBSCMakeFileGenerator(pack, optHandler.getSbsXmlPath(), false);
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
			else if(phase == Phase.CLEAN){
				Logger.info("----------- begin clean -----------");
				SBSCMakeCleaner cleaner = new SBSCMakeCleaner();
				cleaner.clean(pack, optHandler.getSbsXmlPath());
				Logger.info("------------ end clean ------------");
			}
			else if(phase == Phase.LOAD_XML_TEST){
				Logger.info("--------- begin data fill ---------");
				dataFiller.fill(doc,true);
				if(!checkErrors()) return;
				Logger.info("---------- end data fill ----------");
			}
			else if(phase == Phase.CHECK_TEST){
				Logger.info("----- begin check test fields -----");
				checkFields(testPack);
				if(!checkErrors()) return;
				Logger.info("------ end check test fields ------");
			}
			else if(phase == Phase.GENERATE_TEST){
				Logger.info("----- begin generate test makefile -----");
				SBSCMakeFileGenerator generator = new SBSCMakeFileGenerator(testPack, optHandler.getSbsXmlPath()+"test/", true);
				generator.generate();
				if(!checkErrors()) return;
				SBSCMakeLauncher launcher = new SBSCMakeLauncher();
				launcher.launch(optHandler.getSbsXmlPath()+"test/");
				if(!checkErrors()) return;
				Logger.info("------ end generate test makefile ------");
			}
			else if(phase == Phase.COMPILE_TEST){
				Logger.info("-------- begin compilation --------");
				Logger.warning("TODO");
				Logger.info("--------- end compilation ---------");
			}
			else if(phase == Phase.CLEAN_TEST){
				Logger.info("-------- begin clean test ---------");
				SBSCMakeCleaner cleaner = new SBSCMakeCleaner();
				cleaner.clean(testPack, optHandler.getSbsXmlPath()+"test/");
				Logger.info("--------- end clean test ----------");
			}
			else if(phase == Phase.TEST){
				Logger.info("----------- begin test ------------");
				Logger.warning("TODO");
				Logger.info("------------ end test -------------");
			}
		}
		
		Logger.info("------------- end SBS -------------");
		Logger.info("");
		Logger.info("-----------------------------------");
		Logger.info("        COMMAND SUCCESSFUL         ");
		Logger.info("-----------------------------------");
	}
}
