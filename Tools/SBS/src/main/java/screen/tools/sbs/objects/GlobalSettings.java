package screen.tools.sbs.objects;

public class GlobalSettings {
	private static GlobalSettings globalSettings = new GlobalSettings();
	private EnvironmentVariables envVar;
	private ErrorList errorList;
	private boolean debug;
	
	private GlobalSettings() {
		envVar = new EnvironmentVariables();
		errorList = new ErrorList();
		debug = false;
	}
	
	public static GlobalSettings getGlobalSettings() {
		return globalSettings;
	}

	public EnvironmentVariables getEnvironmentVariables() {
		return envVar;
	}
	
	public ErrorList getErrorList(){
		return errorList;
	}

	public void setDebug(boolean debug) {
		this.debug = debug;
	}

	public boolean isDebug() {
		return debug;
	}

	public void setError(boolean b) {
		errorList.setLogError(b);
	}
	
}
