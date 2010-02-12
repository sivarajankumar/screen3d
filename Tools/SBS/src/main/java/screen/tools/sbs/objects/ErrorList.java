package screen.tools.sbs.objects;

import java.util.ArrayList;
import java.util.List;

import screen.tools.sbs.utils.Logger;

public class ErrorList {
	private List<String> errorList;
	private List<String> warningList;
	private boolean logError;
	
	public ErrorList() {
		errorList = new ArrayList<String>();
		warningList = new ArrayList<String>();
		logError = true;
	}
	
	public void addError(String error){
		if(logError){
			errorList.add(error);
		}
	}
	
	public void addWarning(String warning){
		if(logError){
			warningList.add(warning);
		}
	}
	
	public void displayErrors(){
		for(int i=0; i<errorList.size(); i++){
			Logger.error(errorList.get(i));
		}
	}
	
	public void displayWarnings(){
		for(int i=0; i<warningList.size(); i++){
			Logger.error(warningList.get(i));
		}
	}
	
	public boolean hasErrors(){
		return !errorList.isEmpty();
	}
	
	public boolean hasWarnings(){
		return !warningList.isEmpty();
	}
	
	public List<String> getErrors(){
		return errorList;
	}
	
	public List<String> getWarnings(){
		return warningList;
	}

	public void setLogError(boolean b) {
		logError = true;
	}
}
