function TabCreator(god) {
	this.god = god;

	this.god.tabCreated.connect(this.progTabCreated.bind(this));

	return this;
}

TabCreator.prototype.progTabCreated = function(uuid) {
	var tab = new Tab(uuid, this);
}
