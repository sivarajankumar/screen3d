/*****************************************************************************
 * This source file is part of SBS (Screen Build System),                    *
 * which is a component of Screen Framework                                  *
 *                                                                           *
 * Copyright (c) 2008-2010 Ratouit Thomas                                    *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Lesser General Public License as published by  *
 * the Free Software Foundation; either version 3 of the License, or (at     *
 * your option) any later version.                                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser   *
 * General Public License for more details.                                  *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this program; if not, write to the Free Software Foundation,   *
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA, or go to   *
 * http://www.gnu.org/copyleft/lesser.txt.                                   *
 *****************************************************************************/

package screen.tools.sbs.objects;

import java.util.ArrayList;
import java.util.List;

import screen.tools.sbs.utils.FieldBool;
import screen.tools.sbs.utils.FieldPath;
import screen.tools.sbs.utils.FieldString;

public class Dependency {
	private FieldString name;
	private FieldString version;
	private FieldBool export;
	private List<FieldPath> includePathList;
	private List<FieldPath> libraryPathList;
	private List<Library> libraryList;
	
	public Dependency() {
		name = new FieldString();
		version = new FieldString();
		export = new FieldBool();
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
	
	public void setExport(FieldBool export) {
		this.export = export;
	}
	
	public FieldBool getExport() {
		return export;
	}
	
	public boolean getSbs() {
		if(name!=null && version!=null)
			return name.isValid() && version.isValid();
		return false;
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

	public void addLibrary(Library library) {
		libraryList.add(library);
	}
}