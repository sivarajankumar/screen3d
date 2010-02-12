package screen.tools.sbs.objects;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Properties;

import screen.tools.sbs.utils.Logger;

public class EnvironmentVariables {
	private Hashtable<String, String> variableTable;
	
	public EnvironmentVariables() {
		variableTable = new Hashtable<String, String>();
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
			variableTable.put(key, value);
		}
	}
	
	public void put(String variable, String value) {
		variableTable.put(variable, value);
	}
	
	public boolean contains (String variable){
		return variableTable.containsKey(variable);
	}
	
	public String getValue(String variable){
		return variableTable.get(variable);
	}
}
