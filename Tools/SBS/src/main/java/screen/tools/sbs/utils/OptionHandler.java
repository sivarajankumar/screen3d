package screen.tools.sbs.utils;

import java.util.ArrayList;
import java.util.List;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;

public class OptionHandler {
	public enum Phase{
		LOAD_CONF,
		LOAD_XML,
		CHECK,
		GENERATE,
		COMPILE,
		CHECK_TEST,
		GENERATE_TEST,
		COMPILE_TEST,
		TEST
	}
	private String sbsXmlPath;
	private List<Phase> phaseList; 
	
	public OptionHandler(String[] args) {
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		phaseList = new ArrayList<Phase>();
		if(args.length == 0){
			err.addError("No parameters");
		}
		else if(args.length == 1){
			if("-h".equals(args[0])){
				usage();
			}
			else {
				err.addError("Bad parameter : " + args[0]);
			}
		}
		else{
			sbsXmlPath = args[0];
			if(!sbsXmlPath.endsWith("/"))
				sbsXmlPath += "/";
			String phase = args[1];
			
            GlobalSettings.getGlobalSettings().getEnvironmentVariables().put("_COMPILE_MODE", "Release");
            
			boolean hasMainBuild = true;
			boolean hasTestBuild = false;
            
            for(int i=2; i<args.length; i++){
				String option = args[i];
				if("-v".equals(option)){
					GlobalSettings.getGlobalSettings().setDebug(true);
				} else if("-d".equals(option)){
					GlobalSettings.getGlobalSettings().getEnvironmentVariables().put("_COMPILE_MODE", "Debug");
				} else if("-e".equals(option)){
					if(i+1>=args.length){
						err.addError("Bad parameter / no env config : ");
					}
					else{
						String root = System.getProperty("SBS_ROOT");
						GlobalSettings.getGlobalSettings().getEnvironmentVariables().putFromFile(root+"/"+args[i+1]+".config");
						i++;
					}
				} else if("-t".equals(option)){
					hasMainBuild = false;
					hasTestBuild = true;
				} else if("-b".equals(option)){
					hasTestBuild = true;
				}
			}
			
			if("check".equals(phase)){
            	phaseList.add(Phase.LOAD_CONF);
    			phaseList.add(Phase.LOAD_XML);
				phaseList.add(Phase.CHECK);
			}
            else if("generate".equals(phase)){
            	phaseList.add(Phase.LOAD_CONF);
    			phaseList.add(Phase.LOAD_XML);
				if(hasMainBuild){
					phaseList.add(Phase.CHECK);
					phaseList.add(Phase.GENERATE);
				}
				if(hasTestBuild){
					phaseList.add(Phase.CHECK_TEST);
					phaseList.add(Phase.GENERATE_TEST);
				}
			}
			else if("compile".equals(phase)){
				if(hasMainBuild){
					phaseList.add(Phase.COMPILE);
				}
				if(hasTestBuild){
					phaseList.add(Phase.COMPILE_TEST);
				}
			}
			else if("test".equals(phase)){
				phaseList.add(Phase.TEST);
			}
			else if("build".equals(phase)){
				phaseList.add(Phase.LOAD_CONF);
				phaseList.add(Phase.LOAD_XML);
				if(hasMainBuild){
					phaseList.add(Phase.CHECK);
					phaseList.add(Phase.GENERATE);
					phaseList.add(Phase.COMPILE);
				}
				if(hasTestBuild){
					phaseList.add(Phase.CHECK_TEST);
					phaseList.add(Phase.GENERATE_TEST);
					phaseList.add(Phase.COMPILE_TEST);
				}
			}
			else{
				err.addError("Bad parameter / unknown phase : " + phase);
			}
		}
	}
	
	public String getSbsXmlPath(){
		return sbsXmlPath;
	}
	
	public void usage(){
		Logger.info("Usage :");
		Logger.info("    parameters : <path-to-sbs.xml> <phase> -[options]");
		Logger.info("    phase :");
		Logger.info("        check : verify configuration");
		Logger.info("        generate : generate makefiles");
		Logger.info("        compile  : compile pack sources");
		Logger.info("        build  : generate+compile");
		Logger.info("        test  : launch tests");
		Logger.info("    options :");
		Logger.info("        -e <config file> : set specific environment configurations");
		Logger.info("        -v : verbose (debug mode)");
		Logger.info("        -d : debug compile");
		Logger.info("        -t : tests");
	}
	
	public List<Phase> getPhaseList(){
		return phaseList;
	}
}
