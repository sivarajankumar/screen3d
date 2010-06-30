package screen.tools.sbs.utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;

public class ProcessLauncher {

	private Process process;
	
	public static String getCommand(String[] command){
		String comStr = "";
    	for(int i = 0; i<command.length; i++){
    		comStr+=command[i];
    		if(i+1<command.length)
    			comStr+=" ";
    	}
		return comStr;
	}
	
	public ProcessLauncher() {
		process = null;
	}
	
	public InputStream getInputStream() {
		return process.getInputStream();
	}
	
	public OutputStream getOutputStream() {
		return process.getOutputStream();
	}
	
	public InputStream getErrorStream() {
		return process.getErrorStream();
	}

	public void execute(String command) throws IOException {
		process = Runtime.getRuntime().exec(command);
		execute();
	}
	
	public void execute(String[] cmdarray) throws IOException {
		process = Runtime.getRuntime().exec(cmdarray);
		execute();
	}
	
	public void execute(String[] cmdarray, String[] envp) throws IOException {
		process = Runtime.getRuntime().exec(cmdarray, envp);
		execute();
	}
	
	public void execute(String[] cmdarray, String[] envp, File dir) throws IOException {
		process = Runtime.getRuntime().exec(cmdarray, envp, dir);
		execute();
	}
	
	public void execute(String command, String[] envp) throws IOException {
		process = Runtime.getRuntime().exec(command, envp);
		execute();
	}
	
	public void execute(String command, String[] envp, File dir) throws IOException  {
		process = Runtime.getRuntime().exec(command, envp, dir);
		execute();
	}
	
	private void execute() {
		new Thread() {
		    public void run() {
		        try {
		            process.waitFor();
		        } catch(InterruptedException ie) {
		            ie.printStackTrace();
		        }
		    }
		}.start();
	}

	public void processOutputs() throws IOException {
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		
		BufferedReader stdInput = new BufferedReader(new InputStreamReader(getInputStream()));
        BufferedReader stdError = new BufferedReader(new InputStreamReader(getErrorStream()));

        String s;
		while ((s = stdInput.readLine()) != null) {
			Logger.info(s);
		}
        while ((s = stdError.readLine()) != null) {
            err.addError(s);
        }		
	}
	
	
}