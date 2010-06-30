package screen.tools.sbs;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import screen.tools.sbs.objects.EnvironmentVariables;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.utils.Logger;
import screen.tools.sbs.utils.ProcessLauncher;
import screen.tools.sbs.utils.Utilities;

public class SBSHeaderDeployer {

	public void deploy(String sbsXmlPath, Pack pack) {
		try {
			ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
			EnvironmentVariables variables = GlobalSettings.getGlobalSettings().getEnvironmentVariables();
			
	    	String[] command = null;
	    	
	    	if(!variables.contains("REPOSITORY_ROOT")){
				err.addError("undefined variable : REPOSITORY_ROOT");
			}
			String repoRoot = variables.getValue("REPOSITORY_ROOT");
	    	String packPath = pack.getProperties().getName().getString();
	    	String packVersion = pack.getProperties().getVersion().getString();
	    	String root = System.getProperty("SBS_ROOT");
	    	
	    	if(Utilities.isWindows())
	    		command = new String[]{"cmd.exe", "/C", "/Q", "/E:off", root+"/deploy-header.bat", new File(sbsXmlPath).getAbsolutePath(), repoRoot +"/"+packPath+"/"+packVersion};
	    	else if(Utilities.isLinux())
	    		command = new String[]{"/bin/sh", root+"/deploy-header.sh", new File(sbsXmlPath).getAbsolutePath(), repoRoot +"/"+packPath+"/"+packVersion};
	    	
	    	if(command!=null){
		    	Logger.info("command : "+ProcessLauncher.getCommand(command));
		    	ProcessLauncher p = new ProcessLauncher();
		
				p.execute(command,null,new File(sbsXmlPath));
				
				BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
		
		        BufferedReader stdError = new BufferedReader(new InputStreamReader(p.getErrorStream()));
		
		        String s;
		        while ((s = stdInput.readLine()) != null) {
		        	Logger.info(s);
		        }
		        while ((s = stdError.readLine()) != null) {
		            err.addError(s);
		        }
	    	}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
