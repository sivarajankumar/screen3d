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

package screen.tools.sbs.utils.targethelper;

import java.util.List;

import screen.tools.sbs.objects.ErrorList;
import screen.tools.sbs.objects.GlobalSettings;
import screen.tools.sbs.targets.Parameters;

public class OptionFile implements Option {

	private String option;
	private String file;
	
	public OptionFile(String defaultFile) {
		option = "-i";
		file = defaultFile;
	}

	public OptionFile(String defaultOption, String defaultFile) {
		option = defaultOption;
		file = defaultFile;
	}
	
	public int perform(Parameters pars, int it) {
		ErrorList err = GlobalSettings.getGlobalSettings().getErrorList();
		String par = pars.getParameterAt(it);
		if(option.equals(par)){
			if(it+1<pars.size()){
				file = pars.getParameterAt(it+1);
				it++;
			}
			else{
				err.addError("Missing parameter / \""+option+"\" option without file name");
				GlobalSettings.getGlobalSettings().needUsage();
			}
			return it;
		}
		return -1;
	}

	public String getFile(){
		return file;
	}

	public void usage(List<String> manUsage) {
		manUsage.add(option+" <sbs-file> : select specific sbs xml file");
	}
}
