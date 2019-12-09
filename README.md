# Task for QE hiring prospects

You will make a small application in a programming language of your choice that takes CSV and JSON files as an input. The application should be able to be launched with a simple command, eg.

```bash
./extractor.sh "${path_to_input_json_or_csv}"
```

Example csv file content:

```csv
first_name,last_name,siblings,favourite_food,birth_timezone,birth_timestamp
DELIA,MCCRAE,5,chicken,−08:00,601605300000
EUGENE,VANDERSTEEN,2,Yogurt,+01:00,853371780000
BERNARDINA,STWART,1,Mozzarella cheese,+10:30,285926100000
```

Example json file content:
```json
[
{ "first_name": "LEONEL", "last_name": "FERREL", "siblings": "1", "favourite_food": "Meatballs", "birth_timezone": "−01:00", "birth_timestamp": "917172960000" },
{ "first_name": "SHANNA", "last_name": "HILYER", "siblings": "5", "favourite_food": "Meatballs", "birth_timezone": "−05:00", "birth_timestamp": "884072160000" },
{ "first_name": "CARLI", "last_name": "NEWKIRK", "siblings": "5", "favourite_food": "Candy", "birth_timezone": "+01:00", "birth_timestamp": "600794820000" }
]
```

The application will parse the specified file and print out the following information:

* Average number of siblings (round up)
* Top 3 favourite foods and the number of people who like them
* How many people were born in each month of the year (uses the month of each person's respective timezone of birth)


Example output :
```
Average siblings: 2

Favourite foods:
- Pizza      74
- Meatballs  36
- Ice Cream  33

Births per Month:
- January   654
- February   45
- March      38
- April      28
- May        11
- June       16
- July       13
- August      7
- September  32
- October     5
- November   30
- December   31
```

The application should have a robust test suite written using a standard testing library for the chosen language.

We strongly encourage you to:
* use 3rd party libraries for parsing (ie: fasterxml and/or json)
* take readability into account (comments are appreciated!)
* take performance into account
* ensure that it runs from the command line outside of your preferred IDE.

Assumptions you can make:
* The json and csv formats are valid and have all the fields required.
* The file extension can be relied on to indicate what the type of file.
