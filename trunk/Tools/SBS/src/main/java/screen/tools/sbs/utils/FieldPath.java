package screen.tools.sbs.utils;

import screen.tools.sbs.objects.EnvironmentVariables;

public class FieldPath {
	FieldString fieldString;
	FieldBuildMode fieldBuildMode; 
	
	public FieldPath() {
		fieldString = new FieldString();
		fieldBuildMode = new FieldBuildMode();
	}
	
	public FieldPath(String path) {
		fieldString = new FieldString(path);
		fieldBuildMode =  new FieldBuildMode();
	}
	
	public boolean isEmpty(){
		return fieldString.isEmpty();
	}
	
	public boolean isValid(EnvironmentVariables additionalVars){
		return fieldString.isValid(additionalVars);
	}

	public boolean isValid(){
		return isValid(null);
	}

	public void setString(String path) {
		fieldString.setString(path);
	}

	public String getOriginalString() {
		return fieldString.getOriginalString();
	}
	
	public String getString(EnvironmentVariables additionalVars) {
		String ret = fieldString.getString(additionalVars);
		if(ret == null)
			return null;
		ret = ret.replaceAll("\\\\", "/");
		ret = ret.replaceAll(" ", "\\\\ ");
		if(!ret.endsWith("/"))
			ret += "/";
		return ret;
	}

	public String getString(){
		return getString(null);
	}
	
	public void setBuildMode(FieldBuildMode mode){
		fieldBuildMode = mode;
	}
	
	public FieldBuildMode getBuildMode(){
		return fieldBuildMode;
	}
}
