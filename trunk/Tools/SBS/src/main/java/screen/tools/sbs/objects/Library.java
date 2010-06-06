package screen.tools.sbs.objects;

import screen.tools.sbs.utils.FieldString;

public class Library {
	private FieldString name;
	private FieldString version;
	
	public Library(){
		name = new 	FieldString();
		version = new 	FieldString();
	}

	public void setName(FieldString name) {
		this.name = name;
	}

	public FieldString getName() {
		return name;
	}

	public void setVersion(FieldString version) {
		this.version = version;
	}

	public FieldString getVersion() {
		return version;
	}
}