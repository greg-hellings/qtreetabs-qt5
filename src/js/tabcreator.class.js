function TabCreator(god) {
	this.god = god;
	this.__tabs = {};

	this.god.tabCreated.connect(this.progTabCreated.bind(this));
	// When QWebchannel is updated to allow post-attach registration, this becomes moot
	this.god.tabChanged.connect(this.onTabChanged.bind(this));

	return this;
}

TabCreator.prototype.__getTab = function(uuid) {
	if ( !(uuid in this.__tabs) ) {
		return null;
	}
	return this.__tabs[uuid];
}

TabCreator.prototype.progTabCreated = function(uuid) {
	var tab = new Tab(uuid, this);
	this.__tabs[uuid] = tab;
}

// When QWebchannel is updated to allow post-attach registration, this becomes moot
TabCreator.prototype.onTabChanged = function(old, current) {
	var tab;
	if ( current.uuid in this.__tabs ) {
		tab = this.__tabs[current.uuid];
		tab.activate();
	}
}
