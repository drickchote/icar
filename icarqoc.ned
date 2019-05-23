//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package org.car2x.veins.modules.application.icarnew;
import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;
//
// TODO auto-generated module
//
simple Icarqoc extends BaseWaveApplLayer
{

    parameters:
        @class(Icarqoc);         
        @display("p=60,50");
        string appName = default("Icarqoc!");
        double maxSpeed= default(24.4);// em m/s 88 km/h máximo da via + 10% tolerado em lei municipal
        double radiusSet = default(250); // valor baseado no artigo XXXXXXXXX meters 
        double perforMesurementPeriod = default(1); // Período de medição do desempeno da comunicação do agente CommPerformance
        double monitorPeriod = default(1); // Período de monitoração beacon msg         
}
