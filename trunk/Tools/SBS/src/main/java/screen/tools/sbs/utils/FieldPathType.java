package screen.tools.sbs.utils;

public class FieldPathType {
	public enum Type{
		ABSOLUTE,
		RELATIVE
	}
	
	Type position;
	
	public FieldPathType() {
		position = Type.RELATIVE;
	}
	
	public void set(Type position){
		this.position = position;
	}
	
	public Type get(){
		return position;
	}
	
	public void set(String pos){
		FieldString fs = new FieldString(pos);
		if(fs.isValid()){
			String pos2 = fs.getString();
			if("absolute".equals(pos2)){
				position = Type.ABSOLUTE;
			}
			else if("relative".equals(pos2)){
				position = Type.RELATIVE;
			}
		}
	}
	
	public FieldPath getFieldPath(String root, String relative){
		if(position == Type.ABSOLUTE){
			return new FieldPath(relative);
		}
		else{
			return new FieldPath(root+"/"+relative);
		}
	}
	
	public FieldFile getFieldFile(String root, String relative){
		if(position == Type.ABSOLUTE){
			return new FieldFile(relative);
		}
		else{
			return new FieldFile(root+"/"+relative);
		}
	}
}
