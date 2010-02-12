package screen.tools.sbs.cmake;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

import screen.tools.sbs.objects.Dependency;
import screen.tools.sbs.objects.EnvironmentVariables;
import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.Flag;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.FieldString;

public class SBSCMakeFileGenerator {
	public Pack pack;
	String sbsXmlPath;
	
	public SBSCMakeFileGenerator(Pack pack, String sbsXmlPath) {
		this.pack = pack;
		this.sbsXmlPath = sbsXmlPath;
	}
	
	public void generate() {
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		
		File cmakeListFile = new File(sbsXmlPath + "CMakeLists.txt");
		FileWriter cmakeListWriter = null;
		try {
			cmakeListWriter = new FileWriter(cmakeListFile,false);
		} catch (FileNotFoundException e) {
			err.addError("Can't create file CMakeLists.txt");
			return;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			err.addError(e.getMessage());
			return;
		}
		
		try {
			String packName = pack.getProperties().getName().getString().replaceAll("/", "");
			
			EnvironmentVariables variables = GlobalSettings.getGlobalSettings().getEnvironmentVariables();
			
			String compileMode = variables.getValue("_COMPILE_MODE");
			boolean isDebugMode = "Debug".equals(compileMode);
			String flagVar = compileMode.toUpperCase()+"_FLAGS";
			if(!variables.contains(flagVar)){
				err.addError("undefined variable : "+flagVar);
			}
			String flagString = variables.getValue(flagVar);
			String[] flags = flagString.split(" ");
			
			String packBuildType = pack.getProperties().getBuildType().getString();
			boolean hasLibBuild = "static".equals(packBuildType) || "shared".equals(packBuildType);
			String sharedLibBuild = "shared".equals(packBuildType) ? "ON" : "OFF";
			
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
			
			
			cmakeListWriter.write("CMAKE_MINIMUM_REQUIRED(VERSION 2.6)\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("PROJECT("+ packName +")\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("SET(${PROJECT_NAME}_VERSION \""+ pack.getProperties().getVersion().getString() +"\")\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("SET(CMAKE_BUILD_TYPE \""+ compileMode +"\")\n");
			cmakeListWriter.write("\n");
			if(hasLibBuild){
				cmakeListWriter.write("OPTION(BUILD_SHARED_LIBS "+ sharedLibBuild +")\n");
				cmakeListWriter.write("\n");
			}
			for(int i=0; i<flags.length; i++){
				if(!"".equals(flags[i])){
					cmakeListWriter.write("ADD_DEFINITIONS(\"-D"+ flags[i] +"\")\n");
				}
			}
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
			cmakeListWriter.write("\n");
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
			cmakeListWriter.write("\n");
			cmakeListWriter.write("INCLUDE_DIRECTORIES(\n");
			cmakeListWriter.write("    src\n");
			cmakeListWriter.write("    include\n");
			for(int i=0; i<deps.size(); i++){
				List<FieldPath> paths = deps.get(i).getIncludePathList();
				for(int j=0; j<paths.size(); j++){
					cmakeListWriter.write("    "+ paths.get(j).getString() +"\n");
				}
			}
			cmakeListWriter.write(")\n");
			cmakeListWriter.write("\n");
			cmakeListWriter.write("LINK_DIRECTORIES(\n");
			for(int i=0; i<deps.size(); i++){
				List<FieldPath> paths = deps.get(i).getLibraryPathList();
				for(int j=0; j<paths.size(); j++){
					cmakeListWriter.write("    "+ paths.get(j).getString() +"\n");
				}
			}
			cmakeListWriter.write("    "+ repoRoot +"/"+envName+"/"+ compileMode +"\n");
			cmakeListWriter.write(")\n");
			cmakeListWriter.write("\n");
			if(hasLibBuild)
				cmakeListWriter.write("SET(LIBRARY_OUTPUT_PATH "+ repoRoot +"/"+envName+"/"+ compileMode +")\n");
			else
				cmakeListWriter.write("SET(EXECUTABLE_OUTPUT_PATH "+ repoRoot +"/"+envName+"/"+ compileMode +")\n");
			cmakeListWriter.write("\n");
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
			cmakeListWriter.write("TARGET_LINK_LIBRARIES(\n");
			cmakeListWriter.write("    ${PROJECT_NAME}\n");
			for(int i=0; i<deps.size(); i++){
				List<FieldString> libs = deps.get(i).getLibraryNameList();
				for(int j=0; j<libs.size(); j++){
					cmakeListWriter.write("    "+ libs.get(j).getString() +"\n");
				}
			}
			cmakeListWriter.write(")\n");
			cmakeListWriter.write("\n");
			
			cmakeListWriter.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			err.addError(e.getMessage());
		}
	}
	
	public void generateTest() {
		
	}
}
