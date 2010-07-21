package screen.tools.sbs.utils;

import screen.tools.sbs.utils.FieldString;

public class FieldBuildType {
	
	public enum Type{
		EXECUTABLE,
		STATIC_LIBRARY,
		SHARED_LIBRARY
	}
	
	Type type;
	
	public FieldBuildType() {
		type = Type.EXECUTABLE;
	}
	
	public void set(FieldBuildType.Type type){
		this.type = type;
	}
	
	public void set(String value){
		FieldString field = new FieldString(value);
		String string = field.getString();
		if("static".equals(string)){
			type = Type.STATIC_LIBRARY;
		}
		else if ("shared".equals(string)){
			type = Type.SHARED_LIBRARY;
		}
		else{
			type = Type.EXECUTABLE;
		}
	}
	
	public Type get() {
		return type;
	}
}
