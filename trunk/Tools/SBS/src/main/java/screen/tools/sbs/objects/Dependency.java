package screen.tools.sbs.objects;

import java.util.ArrayList;
import java.util.List;

import screen.tools.sbs.utils.FieldBool;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.FieldString;

public class Dependency {
	private FieldString name;
	private FieldString version;
	private FieldPath root;
	private FieldBool isSbs;
	private List<FieldPath> includePathList;
	private List<FieldPath> libraryPathList;
	private List<Library> libraryList;
	
	public Dependency() {
		name = new FieldString();
		version = null;
		root = new FieldPath();
		isSbs = new FieldBool();
		includePathList = new ArrayList<FieldPath>();
		libraryPathList = new ArrayList<FieldPath>();
		libraryList = new ArrayList<Library>();
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
	
	public void setRoot(FieldPath root) {
		this.root = root;
	}

	public FieldPath getRoot() {
		return root;
	}
	
	public void setSbs(FieldBool isSbs) {
		this.isSbs = isSbs;
	}

	public FieldBool getSbs() {
		return isSbs;
	}
	
	public void addIncludePath(FieldPath include){
		includePathList.add(include);
	}
	
	public void addLibraryPath(FieldPath include){
		libraryPathList.add(include);
	}
	
	public void addLibrary(FieldString name){
		Library lib = new Library();
		lib.setName(name);
		libraryList.add(lib);
	}

	public void addLibrary(FieldString name, FieldString version){
		Library lib = new Library();
		lib.setName(name);
		lib.setVersion(version);
		libraryList.add(lib);
	}


	public void setIncludePathList(List<FieldPath> includePathList) {
		this.includePathList = includePathList;
	}

	public List<FieldPath> getIncludePathList() {
		return includePathList;
	}
	
	public void setLibraryPathList(List<FieldPath> libraryPathList) {
		this.libraryPathList = libraryPathList;
	}

	public List<FieldPath> getLibraryPathList() {
		return libraryPathList;
	}

	public void setLibraryNameList(List<Library> libraryList) {
		this.libraryList = libraryList;
	}

	public List<Library> getLibraryList() {
		return libraryList;
	}
}