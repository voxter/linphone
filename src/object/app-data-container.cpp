/*
 * app-data-container.cpp
 * Copyright (C) 2010-2017 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <memory>

#include "app-data-container.h"

// =============================================================================

using namespace std;

LINPHONE_BEGIN_NAMESPACE

class AppDataContainerPrivate {
public:
	shared_ptr<unordered_map<string, string>> appData;
};

// -----------------------------------------------------------------------------

AppDataContainer::AppDataContainer () : mPrivate(new AppDataContainerPrivate) {
	L_D();
	d->appData = make_shared<unordered_map<string, string>>();
}

AppDataContainer::AppDataContainer (const AppDataContainer &src) : mPrivate(new AppDataContainerPrivate) {
	L_D();
	d->appData = src.getPrivate()->appData;
}

AppDataContainer::~AppDataContainer () {
	delete mPrivate;
}

AppDataContainer &AppDataContainer::operator= (const AppDataContainer &src) {
	L_D();
	if (this != &src)
		d->appData = src.getPrivate()->appData;
	return *this;
}

const unordered_map<string, string> &AppDataContainer::getAppDataMap () const {
	L_D();
	return *d->appData.get();
}

string AppDataContainer::getAppData (const string &name) const {
	L_D();
	auto it = d->appData->find(name);
	return it == d->appData->cend() ? string() : it->second;
}

void AppDataContainer::setAppData (const string &name, const string &appData) {
	L_D();
	(*d->appData)[name] = appData;
}

void AppDataContainer::setAppData (const string &name, string &&appData) {
	L_D();
	(*d->appData)[name] = move(appData);
}

LINPHONE_END_NAMESPACE
