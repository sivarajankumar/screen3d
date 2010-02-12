package screen.tools.sbs.utils;

import screen.tools.sbs.objects.EnvironmentVariables;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;

public class FieldString {
	private String originalString;

	public FieldString() {
		originalString = null;
	}
	
	public FieldString(String value){
		// copy value
		originalString = new String(value);
	}
	
	public boolean isEmpty(){
		return originalString == null;
	}
	
	public boolean isValid(){
		return !isEmpty() && (convertFromOriginalToFinal(originalString)!=null);
	}

	public void setString(String originalString) {
		this.originalString = originalString;
	}

	public String getOriginalString() {
		return originalString;
	}
	
	public String getString() {
		if(!isEmpty())
			return convertFromOriginalToFinal(originalString);
		return null;
	}
	
	private String convertFromOriginalToFinal(String originalString){
		String finalString = "";
		Logger.debug("originalString : "+originalString);
		Logger.debug("finalString : "+finalString);
		boolean isValid = true;
		int currentIndex = 0;
		int returnedIndex = 0;
		EnvironmentVariables env = GlobalSettings.getGlobalSettings().getEnvironmentVariables();
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		
		while((returnedIndex = originalString.indexOf("${", currentIndex)) != -1){
			Logger.debug("originalString : "+originalString);
			Logger.debug("finalString : "+finalString);
			finalString = finalString.concat(originalString.substring(currentIndex, returnedIndex));
			int endVarIndex = 0;
			if((endVarIndex = originalString.indexOf("}", returnedIndex)) == -1){
				err.addError("variable never ended by } caracter : "
							  + originalString.substring(returnedIndex, endVarIndex));
				isValid = false;
			}
			else{
				String var = originalString.substring(returnedIndex+2, endVarIndex);
				Logger.debug("var : "+var);
				if(env.contains(var)){
					finalString = finalString.concat(env.getValue(var));
				}
				else {
					err.addError("undefined variable : "+var);
					isValid = false;
				}
				currentIndex = endVarIndex + 1;
			}
		}
		finalString = finalString.concat(originalString.substring(currentIndex));
		Logger.debug("originalString : "+originalString);
		Logger.debug("finalString : "+finalString);
		if(isValid)
			return finalString;
		else
			return null;
	}
}
