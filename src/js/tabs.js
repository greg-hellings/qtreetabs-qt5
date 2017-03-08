var fn = function() {};
jQuery(function() {
	// Local variables
	var resize = function() {
			qtab.doc.height(qtab.win.height());
			qtab.doc.width(qtab.win.width())
		};
	// Global namespace variable
	window.qtab = {
		doc : jQuery('#all'),
		win : jQuery(window),
		template : jQuery('<div id="template" class="tab"><img src="." /><span>New Tab</span></div>')
	};
	// Get some basic setup going
	resize();
	qtab.win.resize(resize);

	// Connect to the native application
	new QWebChannel(qt.webChannelTransport, function(channel) {
		qtab.god = channel.objects.god;
		qtab.doc.html('');

		// Report to the heavens when user requests a new tab
		qtab.doc.click(function(event) {
			if (event.which == 2) {
				qtab.god.tabRequested();
			}
		});
		qtab.doc.dblclick(function() {
			qtab.god.tabRequested();
		});

		// Listen to god and add a new tab when he tells us to
		qtab.godListener = new TabCreator(qtab.god);
	});
});
