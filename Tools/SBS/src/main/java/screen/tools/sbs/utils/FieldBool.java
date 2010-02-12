package screen.tools.sbs.utils;

public class FieldBool{
	String value;
	
	public FieldBool() {
		value = null;
	}
	
	public FieldBool(String value) {
		this.value = value;
	}
	
	public boolean isEmpty(){
		return value == null;
	}
	
	public boolean isValid(){
		return !isEmpty() && ("true".equals(value) || "false".equals(value));
	}
	
	public boolean getBool() {
		return "true".equals(value);
	}
	
	public void setString(String value){
		this.value = value;
	}
	
	public String getString(){
		return getBool() ? "true" : "false";
	}
	
	public String getOriginalString(){
		return value;
	}
	
}
