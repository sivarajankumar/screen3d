package screen.tools.sbs.objects;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Properties;

import screen.tools.sbs.utils.FieldString;
import screen.tools.sbs.utils.Logger;

public class EnvironmentVariables {
	private Hashtable<String, FieldString> variableTable;
	
	public EnvironmentVariables() {
		variableTable = new Hashtable<String, FieldString>();
	}
	
	public void putFromFile(String filePath){
		File path = new File(filePath);
		Properties properties = new Properties();
		try{
			properties.load(new FileInputStream(path));
		}catch(IOException e){
			Logger.debug(e.getMessage());
			Logger.warning("file "+path.getAbsolutePath()+" not found => no environment variable");
		}
		
		Enumeration<Object> en = properties.keys();
		while(en.hasMoreElements()){
			String key = (String) en.nextElement();
			String value = properties.getProperty(key);
			variableTable.put(key, new FieldString(value));
		}
	}
	
	public void put(String variable, String value) {
		Logger.debug("add var");
		Logger.debug("   key : "+variable);
		Logger.debug("   value : "+value);
		variableTable.put(variable, new FieldString(value));
	}
	
	public boolean contains (String variable){
		if(!variableTable.containsKey(variable))
			return false;
		return getFieldString(variable).getOriginalString() != null;
	}
	
	public String getValue(String variable){
		return variableTable.get(variable).getString();
	}
	
	public String getValue(String variable, EnvironmentVariables addVars){
		return variableTable.get(variable).getString(addVars);
	}
	
	public FieldString getFieldString(String variable){
		return variableTable.get(variable);
	}
}
