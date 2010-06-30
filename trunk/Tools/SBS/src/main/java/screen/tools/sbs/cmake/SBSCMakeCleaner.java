package screen.tools.sbs.cmake;

import java.io.File;
import java.io.IOException;

import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.utils.Logger;
import screen.tools.sbs.utils.ProcessLauncher;
import screen.tools.sbs.utils.Utilities;

public class SBSCMakeCleaner {
	public SBSCMakeCleaner(){}
	
	public void clean(Pack pack, String sbsXmlPath) {
		try {
	    	String[] command = null;
	    	String root = System.getProperty("SBS_ROOT");
	    	
	    	if(Utilities.isWindows())
	    		command = new String[]{"cmd.exe", "/C", "/Q", "/E:off", root+"/clean.bat"};
	    	else if(Utilities.isLinux())
	    		command = new String[]{"/bin/sh", root+"/clean.sh"};
	    	
	    	if(command!=null){
		    	Logger.info("command : "+ProcessLauncher.getCommand(command));
		    	ProcessLauncher p = new ProcessLauncher();
				p.execute(command,null,new File(sbsXmlPath));
				p.processOutputs();
	    	}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
