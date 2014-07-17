Drush SQL Cleanup
===========

When using Drush with Jenkins and GitHub, along with [Lullabots tutorial for deploying Pull Requests](http://lb.cm/mTJ), you may end up deploying each PR into its own database.

This Drush script provides a simple tear-down command:

```
drush sql-drop-database
```

This will drop the database for the site. Feel free to add `@` aliases or `@sites` to drop all site DB's.


## Installation

Simply checkout this repo into ~/.drush (or any of the drush locations for picking up plugins).
