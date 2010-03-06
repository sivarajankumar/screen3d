package screen.tools.sbs.xml;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import screen.tools.sbs.objects.Dependency;
import screen.tools.sbs.objects.Flag;
import screen.tools.sbs.objects.Pack;
import screen.tools.sbs.utils.FieldBool;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.FieldString;
import screen.tools.sbs.utils.Logger;

public class SBSDomDataFiller {
	private Pack pack;
	private static String propertyNameQuery = "//properties/name/text()";
	private static String propertyVersionQuery = "//properties/version/text()";
	private static String propertyBuildTypeQuery = "//properties/buildtype/text()";

	
	public SBSDomDataFiller(Pack pack) {
		this.pack = pack;
	}
	
	public void fill(Document doc){
		//ErrorList errList = GlobalSettings.getGlobalSettings().getErrorList();
		
		Element root = doc.getDocumentElement();
		XPathFactory xFactory = XPathFactory.newInstance();
		XPath query = xFactory.newXPath();
		
		try {
			//properties
			
			//name
			String propertyName = (String) query.compile(propertyNameQuery).evaluate(root);
			Logger.debug("propertyName : "+propertyName);
			pack.getProperties().setName(new FieldString(propertyName));
			
			//version
			String propertyVersion = (String) query.compile(propertyVersionQuery).evaluate(root);
			Logger.debug("propertyVersion : "+propertyVersion);
			pack.getProperties().setVersion(new FieldString(propertyVersion));

			//build type
			String propertyBuildType = (String) query.compile(propertyBuildTypeQuery).evaluate(root);
			Logger.debug("propertyBuildType : "+propertyBuildType);
			pack.getProperties().setBuildType(new FieldString(propertyBuildType));
			
			
			//main
			NodeList main = root.getElementsByTagName("main");
			if(main.getLength() == 1){
				processDependencies((Element) main.item(0),pack);
			}		
		} catch (XPathExpressionException e) {
			e.printStackTrace();
		}
	}

	private void processDependencies(Element root, Pack pack) {
		//dependencies
		Logger.debug("dependencies");
		NodeList depsRoot = root.getElementsByTagName("dependencies");
		if(depsRoot.getLength() == 1){
			NodeList deps = ((Element) depsRoot.item(0)).getElementsByTagName("dependency");
			for(int i=0; i<deps.getLength(); i++){
				//dependency
				Logger.debug("\tdependency");
				Element dep = (Element) deps.item(i);
				Dependency newDep = new Dependency();
				
				String name = dep.getAttribute("name");
				newDep.setName(new FieldString(name));
				
				String depRoot = dep.getAttribute("root");
				newDep.setRoot(new FieldPath(depRoot));
				
				String isSbs = dep.getAttribute("sbs");
				newDep.setSbs(new FieldBool(isSbs));
				if(newDep.getSbs().getBool()){
					newDep.addIncludePath(new FieldPath(depRoot+"/include"));
					//lib path added in CMake file generation
					newDep.addLibraryName(new FieldString(name.replaceAll("/", "")));
				}
				
				// includes
				NodeList inclRoot = dep.getElementsByTagName("includes");
				if(inclRoot.getLength() == 1){
					Logger.debug("\t\tincludes");
					NodeList paths = ((Element) inclRoot.item(0)).getElementsByTagName("path");
					for(int j=0; j<paths.getLength(); j++){
						//path
						Logger.debug("\t\t\tpath");
						Element path = (Element) paths.item(j);
						String pathString = path.getTextContent();
						Logger.debug("\t\t\t\ttext : "+pathString);
						newDep.addIncludePath(new FieldPath(pathString));
					}
				}
				
				//libraries
				NodeList libsRoot = dep.getElementsByTagName("libraries");
				if(libsRoot.getLength() == 1){
					Logger.debug("\t\tlibraries");
					NodeList paths = ((Element) libsRoot.item(0)).getElementsByTagName("path");
					for(int j=0; j<paths.getLength(); j++){
						//path
						Logger.debug("\t\t\tpath");
						Element path = (Element) paths.item(j);
						String pathString = path.getTextContent();
						Logger.debug("\t\t\t\ttext : "+pathString);
						newDep.addLibraryPath(new FieldPath(pathString));
					}
					NodeList libs = ((Element) libsRoot.item(0)).getElementsByTagName("lib");
					for(int j=0; j<libs.getLength(); j++){
						//lib
						Logger.debug("\t\t\tlib");
						Element lib = (Element) libs.item(j);
						String libString = lib.getTextContent();
						Logger.debug("\t\t\t\ttext : "+libString);
						newDep.addLibraryName(new FieldString(libString));
					}
				}
				
				pack.addDependency(newDep);
			}
		}
		
		//flags
		Logger.debug("flags");
		NodeList optsRoot = root.getElementsByTagName("flags");
		if(optsRoot.getLength() == 1){
			NodeList opts = ((Element) optsRoot.item(0)).getElementsByTagName("flag");
			for(int i=0; i<opts.getLength(); i++){
				//dependency
				Logger.debug("\tflag");
				Element opt = (Element) opts.item(i);
				Flag flag = new Flag();
				
				String flagValue = opt.getAttribute("flag");
				flag.setFlag(new FieldString(flagValue));
				Logger.debug("\t\t\tflag : "+flagValue);
				
				String value = opt.getAttribute("value");
				flag.setValue(new FieldString(value));
				Logger.debug("\t\t\tvalue : "+value);
				
				String config = opt.getAttribute("config");
				if(config == null || "".equals(config))
					config = "all";
				flag.setConfig(new FieldString(config));
				Logger.debug("\t\t\tconfig : "+config);
				
				pack.addFlag(flag);
			}
		}

	}
}
