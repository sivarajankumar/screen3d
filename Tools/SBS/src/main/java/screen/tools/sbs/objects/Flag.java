package screen.tools.sbs.objects;

import screen.tools.sbs.utils.FieldString;

public class Flag {
	private FieldString flag;
	private FieldString value;
	private FieldString config;
	
	public Flag() {
		flag = new FieldString();
		value = new FieldString();
		config = new FieldString();
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

	public void setConfig(FieldString config) {
		this.config = config;
	}

	public FieldString getConfig() {
		return config;
	}
	
	
}
