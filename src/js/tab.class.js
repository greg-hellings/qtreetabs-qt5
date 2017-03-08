function Tab(uuid, channel) {
	// Create the dom item and add it to the element
	this.dom = qtab.template.clone();
	this.text = this.dom.find('span');
	qtab.doc.append(this.dom);
	this.dom.show();

	this.__listeners = [];
	this.__uuid = uuid;

	// Listen to events from on high
	if ( channel && channel.onTextChanged ) {
		console.error('Code works, now');
		channel.onTextChanged.connect(this.onTextChanged.bind(this));
	}

	// Add listeners to my dom
	this.dom.click(this.__onClick.bind(this));
	this.dom.dblclick(fn);

	return this;
}

/* Listeners for events from the C++ world */
Tab.prototype.onTextChanged = function(text) {
	this.text.text(text);
}

Tab.prototype.onIconUrlChanged = function(url) {
	this.dom.css('background-image', 'url(' + url + ')');
}

/* Listeners for events from the HTML world */
Tab.prototype.__onClick = function(event) {
	switch (event.button) {
		case 0:
			this.__notifyListeners();
			break;
		case 1:
			break;
		case 2:
			// TODO: Write custom menu
			break;
	}

	return false; // Don't bubble events out of the tab
}

/* Our own event handlers */
Tab.prototype.click = function(callback) {
	this.__listeners.push(callback);
}

Tab.prototype.__notifyListeners = function() {
	this.__listeners.forEach(function(element) {
		try {
			element(this.__uuid);
		} catch(err) {
			console.error(err);
		}
	}.bind(this));
}

/* General member methods */
Tab.prototype.activate = function() {
	jQuery('.tab').removeClass('active');
	this.dom.addClass('active');
}
