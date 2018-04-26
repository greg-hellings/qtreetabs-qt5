function Tab(uuid, tabCreator) {
	// Create the dom item and add it to the element
	this.dom = qtab.template.clone();
	this.text = this.dom.find('span');
	qtab.doc.append(this.dom);
	this.dom.show();

	// Save private values to use later
	this.__god = tabCreator.god;
	this.__uuid = uuid;

	// Add listeners to my dom
	this.dom.on('mouseup', this.middleClick.bind(this));
	this.dom.dblclick(this.requestClose.bind(this));
	this.dom.click(this.click.bind(this));

	// Listen for signals from the C++ side
	this.__god.textChanged.connect(this.progTextChanged.bind(this));
	this.__god.iconUrlChanged.connect(this.progIconUrlChanged.bind(this));
	this.__god.closedTab.connect(this.removeTab.bind(this));
	this.__god.tabChanged.connect(this.progTabChanged.bind(this));

	return this;
}

/**
 * Listeners for events from the C++ world
 */
Tab.prototype.progTextChanged = function(uuid, text) {
	if (this.__uuid == uuid)
		this.text.text(text);
}

Tab.prototype.progIconUrlChanged = function(uuid, url) {
	if (this.__uuid == uuid)
		this.dom.css('background-image', 'url(' + url + ')');
}

Tab.prototype.removeTab = function(uuid, remainint) {
	if (this.__uuid == uuid)
		this.dom.remove();
}

Tab.prototype.progTabChanged = function(oldUuid, newUuid) {
	if (this.__uuid == newUuid) {
		this.dom.addClass('active');
	} else {
		this.dom.removeClass('active');
	}
}

/**
 * Listeners for events from the HTML world
 */
Tab.prototype.middleClick = function(event) {
	if(event.which == 2) {
		this.requestClose();
		return false;
	}
}

Tab.prototype.click = function(event) {
	this.__god.setCurrentTab(this.__uuid);
	return false;
}

/**
 * Send events to the C++ world
 */
Tab.prototype.requestClose = function() {
	this.__god.jsRequestClose(this.__uuid);
	return false;
}
