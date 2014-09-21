var NewsModule = (function() {
  var filters = ''; // приватная переменная
    return { // методы доступные извне
        changeFiltersList: function(id) {
        	if (filters.search(id) == -1)
        	{
        		if (filters.length != 0)
        			filters = filters.concat('-');
        		filters = filters.concat(id);
        	}
        	else 
        	{

        		var parts = filters.split(id);
        		filters = parts[0] + parts[1];

        		if (filters[0] == '-')
        			filters = filters.substr(1);

        		if (filters[filters.length - 1] == '-')
        			filters = filters.substr(0,filters.length - 1);
        		filters = filters.replace('--','-');
        	}
            
        },
        
        filter: function() {
           var newLocation = document.location.href.split('&')[0] + "&f=" + filters;
           if (filters.length > 0)
           {
           	filters = '';
           	document.location = newLocation;
           }
           }
    }
}());