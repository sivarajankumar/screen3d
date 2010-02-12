package screen.tools.sbs.utils;

public class FieldPath {
	FieldString fieldString;
	
	public FieldPath() {
		fieldString = new FieldString();
	}
	
	public FieldPath(String path) {
		fieldString = new FieldString(path);
	}
	
	public boolean isEmpty(){
		return fieldString.isEmpty();
	}
	
	public boolean isValid(){
		return fieldString.isValid();
	}

	public void setString(String path) {
		fieldString.setString(path);
	}

	public String getOriginalString() {
		return fieldString.getOriginalString();
	}
	
	public String getString() {
		String ret = fieldString.getString();
		if(ret == null)
			return null;
		ret = ret.replaceAll("\\\\", "");
		ret = ret.replaceAll(" ", "\\\\ ");
		return ret;
	}
}
