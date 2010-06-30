package screen.tools.sbs.cmake;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

import org.w3c.dom.Document;

import screen.tools.sbs.objects.Dependency;
import screen.tools.sbs.objects.EnvironmentVariables;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.Flag;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.objects.Library;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.FieldString;
import screen.tools.sbs.utils.Logger;
import screen.tools.sbs.utils.ProcessLauncher;
import screen.tools.sbs.utils.Utilities;
import screen.tools.sbs.xml.SBSDomDataFiller;
import screen.tools.sbs.xml.SBSDomParser;

public class SBSCMakeFileGenerator {
	private Pack pack;
	private String sbsXmlPath;
	private boolean isTest;
	
	public SBSCMakeFileGenerator(Pack pack, String sbsXmlPath, boolean isTest) {
		this.pack = pack;
		this.sbsXmlPath = sbsXmlPath;
		this.isTest = isTest;
	}
	
	public void generate() {
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		
		try {
			File cmakeListFile = new File(sbsXmlPath + "CMakeLists.txt");
			FileWriter cmakeListWriter = null;
			try {
				cmakeListWriter = new FileWriter(cmakeListFile,false);
			} catch (FileNotFoundException e) {
				err.addError("Can't create file CMakeLists.txt");
				return;
			}
			
			String packName = pack.getProperties().getName().getString().replaceAll("/", "");
			String packPath = pack.getProperties().getName().getString();
			String packVersion = pack.getProperties().getVersion().getString();
			
			EnvironmentVariables variables = GlobalSettings.getGlobalSettings().getEnvironmentVariables();
			
			//compile mode
			String compileMode = variables.getValue("_COMPILE_MODE");
			boolean isDebugMode = "Debug".equals(compileMode);
			
			//compile mode flags
			String flagVar = compileMode.toUpperCase()+"_FLAGS";
			if(!variables.contains(flagVar)){
				err.addError("undefined variable : "+flagVar);
			}
			String flagString = variables.getValue(flagVar);
			String[] flags = flagString.split(" ");
			
			//build type
			String packBuildType = pack.getProperties().getBuildType().getString();
			boolean hasLibBuild = "static".equals(packBuildType) || "shared".equals(packBuildType);
			String sharedLibBuild = "shared".equals(packBuildType) ? "ON" : "OFF";
			boolean hasSharedLibBuild = "shared".equals(packBuildType); 
			
			List<Dependency> deps = pack.getDependencyList();
			
			if(!variables.contains("REPOSITORY_ROOT")){
				err.addError("undefined variable : REPOSITORY_ROOT");
			}
			String repoRoot = variables.getValue("REPOSITORY_ROOT");
			
			if(!variables.contains("ENV_NAME")){
				err.addError("undefined variable : ENV_NAME");
			}
			String envName = variables.getValue("ENV_NAME");
			
			if(err.hasErrors())
				return;
			
			//CMake headers
			cmakeListWriter.write("CMAKE_MINIMUM_REQUIRED(VERSION 2.6)\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("PROJECT("+ packName +")\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("SET(${PROJECT_NAME}_VERSION \""+ pack.getProperties().getVersion().getString() +"\")\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("SET(CMAKE_BUILD_TYPE \""+ compileMode +"\")\n");
			cmakeListWriter.write("\n");
			
			//library build type 
			if(hasLibBuild){
				cmakeListWriter.write("OPTION(BUILD_SHARED_LIBS "+ sharedLibBuild +")\n");
				cmakeListWriter.write("\n");
			}
			
			//sbs.xml compilation flags
			for(int i=0; i<flags.length; i++){
				if(!"".equals(flags[i])){
					cmakeListWriter.write("ADD_DEFINITIONS(\"-D"+ flags[i] +"\")\n");
				}
			}
			
			//*.config compilation flags
			List<Flag> flagList = pack.getFlagList();
			for(int i=0; i<flagList.size(); i++){
				String config = flagList.get(i).getConfig().getString();
				boolean isDebugFlag = "debug".equals(config) || "all".equals(config);
				boolean isReleaseFlag = "release".equals(config) || "all".equals(config);
				if(isDebugFlag == isDebugMode || isReleaseFlag == (!isDebugMode)){
					String flag = flagList.get(i).getFlag().getString();
					String value = flagList.get(i).getValue().getString();
					if(value == null || "".equals(value)){
						cmakeListWriter.write("ADD_DEFINITIONS(\"-D"+ flag +"\")\n");
					}
					else{
						cmakeListWriter.write("ADD_DEFINITIONS(\"-D"+ flag + "=" + value +"\")\n");
					}
				}
			}
			
			//remove generated files by CMake, in order to not compile them
			cmakeListWriter.write("FILE(REMOVE_RECURSE CMakeFiles/CompilerIdCXX/)\n");
			cmakeListWriter.write("FILE(REMOVE_RECURSE CMakeFiles/CompilerIdC/)\n");
			
			//component include and source files
			if(!isTest){
				cmakeListWriter.write("FILE(\n");
				cmakeListWriter.write("    GLOB_RECURSE\n");
				cmakeListWriter.write("    SRC_FILES\n");
				cmakeListWriter.write("    src/*.cpp\n");
				cmakeListWriter.write("    src/*.c\n");
				cmakeListWriter.write("    src/*.hpp\n");
				cmakeListWriter.write("    src/*.h\n");
				cmakeListWriter.write("    src/*.inl\n");
				cmakeListWriter.write("    src/*.tpp\n");
				cmakeListWriter.write("    src/*.i\n");
				cmakeListWriter.write(")\n");
				cmakeListWriter.write("\n");
				cmakeListWriter.write("FILE(\n");
				cmakeListWriter.write("    GLOB_RECURSE\n");
				cmakeListWriter.write("    INC_FILES\n");
				cmakeListWriter.write("    include/*.hpp\n");	
				cmakeListWriter.write("    include/*.h\n");
				cmakeListWriter.write("    include/*.inl\n");
				cmakeListWriter.write("    include/*.tpp\n");
				cmakeListWriter.write("    include/*.i\n");
				cmakeListWriter.write(")\n");
			} else {
				cmakeListWriter.write("FILE(\n");
				cmakeListWriter.write("    GLOB_RECURSE\n");
				cmakeListWriter.write("    SRC_FILES\n");
				cmakeListWriter.write("    *.cpp\n");
				cmakeListWriter.write("    *.c\n");
				cmakeListWriter.write("    *.hpp\n");
				cmakeListWriter.write("    *.h\n");
				cmakeListWriter.write("    *.inl\n");
				cmakeListWriter.write("    *.tpp\n");
				cmakeListWriter.write("    *.i\n");
				cmakeListWriter.write(")\n");
			}
			cmakeListWriter.write("\n");
			cmakeListWriter.write("INCLUDE_DIRECTORIES(\n");
			if(!isTest){
				cmakeListWriter.write("    src\n");
				cmakeListWriter.write("    include\n");
			}
			else{
				cmakeListWriter.write("    .\n");
			}
			
			//external include paths
			for(int i=0; i<deps.size(); i++){
				Dependency dep = deps.get(i);
				List<FieldPath> paths = dep.getIncludePathList();
				
				//under Windows, all dependencies are in SBS repo
				//under Linux, SBS dependency are in repo, non SBS are in DEFAULT_INCLUDE_PATH
				if(Utilities.isWindows() || (Utilities.isLinux() && dep.getSbs().getBool())){
					//read component.xml to retrieve component include folder path
					Pack componentPack = new Pack();
					Document doc = SBSDomParser.parserFile(new File(repoRoot +"/"+dep.getName().getString()+"/"+dep.getVersion().getString()+"/component.xml"));
					SBSDomDataFiller filler = new SBSDomDataFiller(componentPack, null);
					filler.fill(doc);
					FieldPath componentIncludePath =  componentPack.getDependencyList().get(0).getIncludePathList().get(0);
					FieldPath.Type componentPathType = componentIncludePath.getType();
					String componentPath = componentIncludePath.getString();
					if(componentPathType == FieldPath.Type.RELATIVE)
						componentPath = repoRoot +"/"+dep.getName().getString()+"/"+dep.getVersion().getString()+"/"+componentPath;
					cmakeListWriter.write("    "+componentPath+"\n");
				}
				
				for(int j=0; j<paths.size(); j++){
					cmakeListWriter.write("    "+ paths.get(j).getString() +"\n");
				}
			}
			if(Utilities.isLinux()){
				if(!variables.contains("DEFAULT_INCLUDE_PATH")){
					err.addError("undefined variable : DEFAULT_INCLUDE_PATH");
				}
				String defaultInclude = variables.getValue("DEFAULT_INCLUDE_PATH");
				cmakeListWriter.write("    "+defaultInclude+"\n");
			}
			cmakeListWriter.write(")\n");
			cmakeListWriter.write("\n");
			
			//external library paths
			cmakeListWriter.write("LINK_DIRECTORIES(\n");
			for(int i=0; i<deps.size(); i++){
				Dependency dep = deps.get(i);
				List<FieldPath> paths = dep.getLibraryPathList();
				
				if(Utilities.isWindows()){
					//under Windows, all dependencies are in SBS repo
					cmakeListWriter.write("    "+repoRoot +"/"+dep.getName().getString()+"/"+dep.getVersion().getString()+"/lib/"+envName+"/"+ compileMode+"\n");
				}
				else if(Utilities.isLinux()){
					//under Linux, SBS dependency are in repo, non SBS are in DEFAULT_LIB_PATH
					if(dep.getSbs().getBool())
						cmakeListWriter.write("    "+repoRoot +"/"+dep.getName().getString()+"/"+dep.getVersion().getString()+"/lib/"+envName+"/"+ compileMode+"\n");
				}
				
				for(int j=0; j<paths.size(); j++){
					cmakeListWriter.write("    "+ paths.get(j).getString() +"\n");
				}
			}
			if(Utilities.isLinux()){
				if(!variables.contains("DEFAULT_LIB_PATH")){
					err.addError("undefined variable : DEFAULT_LIB_PATH");
				}
				String defaultInclude = variables.getValue("DEFAULT_LIB_PATH");
				cmakeListWriter.write("    "+defaultInclude+"\n");
			}
			cmakeListWriter.write(")\n");
			cmakeListWriter.write("\n");
			
			//output build path
			if(hasLibBuild)
				cmakeListWriter.write("SET(LIBRARY_OUTPUT_PATH "+ repoRoot +"/"+packPath+"/"+packVersion+"/lib/"+envName+"/"+ compileMode +")\n");
			else
				cmakeListWriter.write("SET(EXECUTABLE_OUTPUT_PATH "+ repoRoot +"/"+packPath+"/"+packVersion+"/exe/"+envName+"/"+ compileMode +")\n");
			cmakeListWriter.write("\n");
			
			//CMake project name
			if(hasLibBuild)
				cmakeListWriter.write("ADD_LIBRARY(\n");
			else
				cmakeListWriter.write("ADD_EXECUTABLE(\n");
			cmakeListWriter.write("    ${PROJECT_NAME}\n");
			if(hasLibBuild)
				cmakeListWriter.write("    "+packBuildType.toUpperCase()+"\n");
			cmakeListWriter.write("    ${SRC_FILES}\n");
			cmakeListWriter.write("    ${INC_FILES}\n");
			cmakeListWriter.write(")\n");
			
			//Dependency library list
			cmakeListWriter.write("TARGET_LINK_LIBRARIES(\n");
			cmakeListWriter.write("    ${PROJECT_NAME}\n");
			for(int i=0; i<deps.size(); i++){
				if(deps.get(i).getSbs().getBool()){
					cmakeListWriter.write("    "+ deps.get(i).getName().getString().replaceAll("/", "") +"\n");
				}
				else {
				List<Library> libs = deps.get(i).getLibraryList();
					for(int j=0; j<libs.size(); j++){
						Library lib = libs.get(j);
						FieldString name = lib.getName();
						FieldString version = lib.getVersion();
						if(version.isEmpty())
							version = deps.get(i).getVersion();
						EnvironmentVariables addVars = new EnvironmentVariables();
						if(name.isValid())
							addVars.put("LIB_NAME", name.getString());
						if(version.isValid())
							addVars.put("LIB_VERSION", version.getString());
						FieldString fullName = new FieldString("${"+deps.get(i).getName().getString().toUpperCase()+"_LIB_PATTERN}");
						if(fullName.isValid(addVars))
							cmakeListWriter.write("    "+ fullName.getString(addVars) +"\n");
					}
				}
			}
			cmakeListWriter.write(")\n");
			cmakeListWriter.write("\n");
			
			cmakeListWriter.close();
			
			//force creation of component root folder
			try {
		    	String[] command = null;
		    	if(Utilities.isWindows())
		    		command = new String[]{};
		    	else if(Utilities.isLinux())
		    		command = new String[]{"/bin/mkdir", "-p", repoRoot +"/"+packPath+"/"+packVersion};
		    	
		    	if(command!=null){
			    	Logger.info("command : "+ProcessLauncher.getCommand(command));
			    	ProcessLauncher p = new ProcessLauncher();
					p.execute(command,null,new File(sbsXmlPath));
					p.processOutputs();
		    	}
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			//self component description file writing
			if(hasLibBuild){
				File sbsComponentFile = new File(repoRoot +"/"+packPath+"/"+packVersion+"/component.xml");
				FileWriter sbsComponentWriter = null;
				try {
					sbsComponentWriter = new FileWriter(sbsComponentFile,false);
				} catch (FileNotFoundException e) {
					err.addError("Can't create file component.xml");
					return;
				}
				sbsComponentWriter.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
				sbsComponentWriter.write("<pack>\n");
				sbsComponentWriter.write("\t<properties>\n");
				sbsComponentWriter.write("\t\t<name>"+packPath+"</name>\n");
				sbsComponentWriter.write("\t\t<version>"+packVersion+"</version>\n");
				sbsComponentWriter.write("\t\t<buildtype>"+packBuildType+"</buildtype>\n");
				sbsComponentWriter.write("\t</properties>\n");
				sbsComponentWriter.write("\t<main>\n");
				sbsComponentWriter.write("\t\t<dependencies>\n");
				sbsComponentWriter.write("\t\t\t<dependency>\n");
				sbsComponentWriter.write("\t\t\t\t<includes>\n");
				sbsComponentWriter.write("\t\t\t\t\t<path>"+new File(sbsXmlPath+"/include").getAbsolutePath()+"</path>\n");
				sbsComponentWriter.write("\t\t\t\t</includes>\n");
				sbsComponentWriter.write("\t\t\t</dependency>\n");
				sbsComponentWriter.write("\t\t</dependencies>\n");
				sbsComponentWriter.write("\t</main>\n");
				sbsComponentWriter.write("</pack>\n");
				sbsComponentWriter.close();
			}
			
			//Symbolic link generation
			if(Utilities.isLinux()){
				//On Linux, generate symbolic links to dynamic libraries and executables
				String root = System.getProperty("SBS_ROOT");
				String[] cmd = null;
				if(hasSharedLibBuild){
				   //shared library
			       cmd = new String[]{"/bin/sh",
							root+"/"+"generate-lib-sym-links.sh",
							packName,
							packVersion,
							repoRoot +"/"+packPath+"/"+packVersion+"/lib/"+envName+"/"+compileMode+"/",
							repoRoot+"/"+envName+"/"+compileMode+"/" };
				}
				else if(!hasLibBuild){
					//executable
					cmd = new String[]{"/bin/sh",
							root+"/"+"generate-exe-sym-links.sh",
							packName,
							packVersion,
							repoRoot +"/"+packPath+"/"+packVersion+"/exe/"+envName+"/"+compileMode+"/",
							repoRoot+"/"+envName+"/"+compileMode+"/" };
				}
				if(cmd!=null){
					Logger.info("command : "+ProcessLauncher.getCommand(cmd));
					
					ProcessLauncher p = new ProcessLauncher();
					p.execute(cmd,null,new File(sbsXmlPath));
					
					BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
			        BufferedReader stdError = new BufferedReader(new InputStreamReader(p.getErrorStream()));
		
		            String s;
			        while ((s = stdInput.readLine()) != null) {
		            	Logger.info(s);
		            }
		            while ((s = stdError.readLine()) != null) {
		            	if(s.contains("ln: creating symbolic link") && s.contains("File exists"))
		            		Logger.debug(s);
		            	else
		            		err.addError(s);
		            }
				}
			}
		} catch (IOException e) {
			err.addError(e.getMessage());
		}
	}
}
