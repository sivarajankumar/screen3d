package screen.tools.sbs.objects;

import screen.tools.sbs.utils.FieldString;

public class ProjectProperties {
	private FieldString name;
	private FieldString version;
	private FieldString buildType;
	
	public ProjectProperties() {
		name = new FieldString();
		version = new FieldString();
		buildType = new FieldString();
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

	public void setBuildType(FieldString buildType) {
		this.buildType = buildType;
	}

	public FieldString getBuildType() {
		return buildType;
	}
}
