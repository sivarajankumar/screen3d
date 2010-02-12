package screen.tools.sbs.utils;

import screen.tools.sbs.objects.GlobalSettings;

public class Logger {
	public static void debug(String s){
		if(GlobalSettings.getGlobalSettings().isDebug())
			System.out.println("[DEBUG] "+s);
	}
	
	public static void info(String s){
		System.out.println("[INFO] "+s);
	}
	
	public static void warning(String s){
		System.out.println("[WARNING] "+s);
	}
	
	public static void error(String s){
		System.out.println("[ERROR] "+s);
	}
}
