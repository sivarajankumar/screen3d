package screen.tools.sbs.cmake;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import screen.tools.sbs.objects.EnvironmentVariables;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.utils.Logger;

public class SBSCMakeLauncher {
	public SBSCMakeLauncher() {}
	
	public void launch(String sbsXmlPath){
		EnvironmentVariables variables = GlobalSettings.getGlobalSettings().getEnvironmentVariables();
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		
		if(!variables.contains("TARGET_ENV")){
			err.addError("undefined variable : TARGET_ENV");
		}
		if(!variables.contains("MAKE_PROGRAM")){
			err.addError("undefined variable : MAKE_PROGRAM");
		}
		if(!variables.contains("C_COMPILER")){
			err.addError("undefined variable : C_COMPILER");
		}
		if(!variables.contains("CPP_COMPILER")){
			err.addError("undefined variable : CPP_COMPILER");
		}
		
		if(err.hasErrors())
			return;
		
		String targetEnv = variables.getValue("TARGET_ENV");
		String makeProg = variables.getValue("MAKE_PROGRAM");
		String cCompiler = variables.getValue("C_COMPILER");
		String cppCompiler = variables.getValue("CPP_COMPILER");
		
		if("/".equals(sbsXmlPath))
			sbsXmlPath=".";
		
		String s = null;

        try {

        	String command ="cmake \""+"."+
        					"\" -G \""+targetEnv+
        					"\" -DCMAKE_MAKE_PROGRAM=\""+makeProg+
        					"\" -DCMAKE_C_COMPILER=\""+cCompiler+
        					"\" -DCMAKE_CXX_COMPILER=\""+cppCompiler+
        					"\"";
        	
        	Logger.info("command : "+command);
        	Process p = Runtime.getRuntime().exec(command,null,new File(sbsXmlPath));
            
            BufferedReader stdInput = new BufferedReader(new 
                 InputStreamReader(p.getInputStream()));

            BufferedReader stdError = new BufferedReader(new 
                 InputStreamReader(p.getErrorStream()));

            while ((s = stdInput.readLine()) != null) {
            	Logger.info(s);
            }
            while ((s = stdError.readLine()) != null) {
                err.addError(s);
            }
        }
        catch (IOException e) {
        	err.addError(e.getMessage());
        }

	}
}
