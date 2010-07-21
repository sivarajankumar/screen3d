package screen.tools.sbs.objects;

import screen.tools.sbs.utils.FieldBuildMode;
import screen.tools.sbs.utils.FieldString;

public class Flag {
	private FieldString flag;
	private FieldString value;
	FieldBuildMode fieldBuildMode;
	
	public Flag() {
		flag = new FieldString();
		value = new FieldString();
		fieldBuildMode = new FieldBuildMode();
	}
	
	public void setFlag(FieldString flag) {
		this.flag = flag;
	}
	public FieldString getFlag() {
		return flag;
	}
	public void setValue(FieldString value) {
		this.value = value;
	}
	public FieldString getValue() {
		return value;
	}
	
	public void setBuildMode(FieldBuildMode mode){
		fieldBuildMode = mode;
	}
	
	public FieldBuildMode getBuildMode(){
		return fieldBuildMode;
	}
}
