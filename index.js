var bindings = require('bindings');
var mathaka_addon = bindings('mathaka');

mathaka_addon.init();

setInterval(function(){console.log(mathaka_addon.memstate());}, 3000);
