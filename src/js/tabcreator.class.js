function TabCreator(god) {
	this.god = god;
	this.__tabs = {};

	this.god.onTabCreated.connect(this.onTabCreated.bind(this));
	// When QWebchannel is updated to allow post-attach registration, this becomes moot
	this.god.onTextChanged.connect(this.onTextChanged.bind(this));
	this.god.onIconUrlChanged.connect(this.onIconUrlChanged.bind(this));
	this.god.onTabChanged.connect(this.onTabChanged.bind(this));

	return this;
}

TabCreator.prototype.onTabCreated = function(uuid) {
	var tab = new Tab(uuid);

	tab.click(this.onTabClick.bind(this));

	this.__tabs[uuid] = tab;
}

// When QWebchannel is updated to allow post-attach registration, this becomes moot
TabCreator.prototype.onTextChanged = function(uuid, newText) {
	var tab;
	if( !(uuid in this.__tabs) ) {
		console.error('Unknown tab');
		return;
	}
	tab = this.__tabs[uuid];
	tab.onTextChanged(newText);
}

TabCreator.prototype.onIconUrlChanged = function(uuid, newUrl) {
	var tab;
	if( !(uuid in this.__tabs) ) {
		console.error('Unknown tab');
		return;
	}
	tab = this.__tabs[uuid];
	tab.onIconUrlChanged(newUrl);
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
