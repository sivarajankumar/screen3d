package screen.tools.sbs.objects;

import java.util.ArrayList;
import java.util.List;

public class Pack {
	private ProjectProperties properties;
	private List<Dependency> dependencyList;
	private List<Flag> flagList;
	
	public Pack(){
		properties = new ProjectProperties();
		dependencyList = new ArrayList<Dependency>();
		flagList = new ArrayList<Flag>();
	}
	
	public void setProperties(ProjectProperties properties) {
		this.properties = properties;
	}
	public ProjectProperties getProperties() {
		return properties;
	}
	
	public void addDependency(Dependency dependency) {
		dependencyList.add(dependency);
	}

	public void setDependencyList(List<Dependency> dependencyList) {
		this.dependencyList = dependencyList;
	}

	public List<Dependency> getDependencyList() {
		return dependencyList;
	}
	
	public void addFlag(Flag flag) {
		flagList.add(flag);
	}

	public void setFlagList(List<Flag> flagList) {
		this.flagList = flagList;
	}

	public List<Flag> getFlagList() {
		return flagList;
	}
}
