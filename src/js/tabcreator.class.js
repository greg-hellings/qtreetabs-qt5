function TabCreator(god) {
	this.god = god;
	this.__tabs = {};

	this.god.tabCreated.connect(this.progTabCreated.bind(this));
	// When QWebchannel is updated to allow post-attach registration, this becomes moot
	this.god.textChanged.connect(this.progTextChanged.bind(this));
	this.god.iconUrlChanged.connect(this.progIconUrlChanged.bind(this));
	this.god.tabChanged.connect(this.onTabChanged.bind(this));

	return this;
}

TabCreator.prototype.progTabCreated = function(uuid) {
	var tab = new Tab(uuid);

	tab.click(this.onTabClick.bind(this));

	this.__tabs[uuid] = tab;
}

// When QWebchannel is updated to allow post-attach registration, this becomes moot
TabCreator.prototype.progTextChanged = function(uuid, newText) {
	var tab;
	if( !(uuid in this.__tabs) ) {
		console.error('Unknown tab');
		return;
	}
	tab = this.__tabs[uuid];
	tab.progTextChanged(newText);
}

TabCreator.prototype.progIconUrlChanged = function(uuid, newUrl) {
	var tab;
	if( !(uuid in this.__tabs) ) {
		console.error('Unknown tab');
		return;
	}
	tab = this.__tabs[uuid];
	tab.progIconUrlChanged(newUrl);
}

TabCreator.prototype.onTabChanged = function(old, current) {
	var tab;
	if ( current.uuid in this.__tabs ) {
		tab = this.__tabs[current.uuid];
		tab.activate();
	}
}

TabCreator.prototype.onTabClick = function(uuid) {
	this.god.setCurrentTab(uuid);
}
