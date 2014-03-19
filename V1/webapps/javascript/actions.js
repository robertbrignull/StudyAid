function goToPage(e, url)
{
	if (e.which == 1)
	{
		window.location = url;
	}
	else if (e.which == 3)
	{
		window.open(url);
	}
}

function confirmAction(url)
{
	if (confirm("Are you sure you want to do this?"))
	{
		window.location = url;
	}
}
