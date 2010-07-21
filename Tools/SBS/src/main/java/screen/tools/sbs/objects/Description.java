package screen.tools.sbs.objects;

import screen.tools.sbs.utils.FieldBuildMode;
import screen.tools.sbs.utils.FieldBuildType;
import screen.tools.sbs.utils.FieldString;

public class Description {
	private FieldString name;
	private FieldString fullName;
	private FieldString compileName;
	private FieldBuildType buildType;
	private FieldBuildMode buildMode;
	
	public Description() {
		name = new FieldString();
		fullName = new FieldString();
		compileName = new FieldString();
		buildType = new FieldBuildType();
		buildMode = new FieldBuildMode();
	}
	
	public void setName(FieldString name) {
		this.name = name;
	}
	
	public void setName(String name) {
		this.name.setString(name);
	}

	public FieldString getName() {
		return name;
	}
	
	public void setFullName(FieldString name) {
		fullName = name;
	}
	
	public void setFullName(String name) {
		fullName.setString(name);
	}

	public FieldString getFullName() {
		return fullName;
	}
	
	public void setCompileName(FieldString name) {
		compileName = name;
	}
	
	public void setCompileName(String name) {
		compileName.setString(name);
	}

	public FieldString getCompileName() {
		return compileName;
	}

	public void setBuildType(FieldBuildType buildType) {
		this.buildType = buildType;
	}
	
	public void setBuildType(String type) {
		buildType.set(type);
	}
	
	public void setBuildType(FieldBuildType.Type type) {
		buildType.set(type);
	}

	public FieldBuildType.Type getBuildType() {
		return buildType.get();
	}
	
	public void setBuildMode(FieldBuildMode buildMode) {
		this.buildMode = buildMode;
	}
	
	public void setBuildMode(String mode) {
		buildMode.set(mode);
	}
	
	public void setBuildMode(FieldBuildMode.Type type) {
		buildMode.set(type);
	}

	public FieldBuildMode getBuildMode() {
		return buildMode;
	}
}
