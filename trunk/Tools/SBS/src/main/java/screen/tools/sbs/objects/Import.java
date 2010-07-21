package screen.tools.sbs.objects;

import screen.tools.sbs.utils.FieldBuildMode;
import screen.tools.sbs.utils.FieldFile;

public class Import {
	private FieldBuildMode buildMode;
	private FieldFile file;
	
	public Import() {
		buildMode = new FieldBuildMode();
		file = new FieldFile();
	}

	public void setBuildMode(FieldBuildMode buildMode) {
		this.buildMode = buildMode;
	}
	
	public void setBuildMode(String mode) {
		buildMode.set(mode);
	}
	
	public void setBuildMode(FieldBuildMode.Type mode) {
		buildMode.set(mode);
	}

	public FieldBuildMode getBuildMode() {
		return buildMode;
	}

	public void setFile(FieldFile file) {
		this.file = file;
	}
	
	public void setFile(String file) {
		this.file.setString(file);
	}

	public FieldFile getFile() {
		return file;
	}
}
