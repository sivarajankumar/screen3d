package screen.tools.sbs.cmake;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.utils.Logger;

public class SBSCMakeCleaner {
	public SBSCMakeCleaner(){}
	
	public void clean(Pack pack, String sbsXmlPath) {
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		String s = null;
		
		try {
        	String command ="cmd.exe /C /Q /E:off sbs_clean.bat ";
       		command+=pack.getProperties().getName().getString().replaceAll("/", "");
        	
        	Logger.info("command : "+command);
        	
        	Process p = Runtime.getRuntime().exec(command,null,new File(sbsXmlPath));
        	Logger.info("coucou");
        	p.waitFor();
        	
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
        } catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
