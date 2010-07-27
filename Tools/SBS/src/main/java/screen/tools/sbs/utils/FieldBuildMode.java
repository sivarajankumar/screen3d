package screen.tools.sbs.utils;

import screen.tools.sbs.utils.FieldString;

public class FieldBuildMode {
	
	public enum Type{
		ALL,
		RELEASE,
		DEBUG
	}
	
	Type type;
	
	public FieldBuildMode() {
		type = Type.ALL;
	}
	
	public FieldBuildMode(FieldBuildMode.Type type){
		this.type = type;
	}
	
	public FieldBuildMode(String string) {
		type = Type.ALL;
		set(string);
	}
	
	public void set(FieldBuildMode.Type type){
		this.type = type;
	}
	
	public void set(String value){
		FieldString field = new FieldString(value);
		String string = field.getString();
		if("release".equals(string)){
			type = Type.RELEASE;
		}
		else if ("debug".equals(string)){
			type = Type.DEBUG;
		}
		else{
			type = Type.ALL;
		}
	}
	
	public Type get() {
		return type;
	}
	
	public String getAsString() {
		switch (type) {
		case DEBUG:
			return "debug";
		case RELEASE:
			return "debug";
		default:
			return "all";
		}
	}
	
	public boolean isSameMode(boolean isRelease){
		if(type == Type.ALL)
			return true;
		else if(type == Type.RELEASE && isRelease)
			return true;
		else if(type == Type.DEBUG && !isRelease)
			return true;
		else
			return false;
	}
}
