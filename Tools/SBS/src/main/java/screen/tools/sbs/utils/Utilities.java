package screen.tools.sbs.utils;

public class Utilities {
	public static boolean isLinux(){
		return "Linux".equals(System.getProperty("os.name"));
	}
	
	public static boolean isWindows(){
		return !isLinux();
	}
}
