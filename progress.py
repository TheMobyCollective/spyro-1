import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as ticker
from git import Repo
import pandas as pd
import datetime
import os
import re

# Read the commits
repo = Repo(os.path.dirname(os.path.realpath(__file__)))
commits = list(repo.iter_commits(paths='progress.md'))

# Read the progress.md file in each commit
progress = []

for commit in commits:
    # Get the date of the commit
    # Make it UTC to avoid timezone issues
    date = commit.committed_datetime
    date = datetime.datetime(date.year, date.month, date.day, 0, 0, 0, tzinfo=datetime.timezone.utc)

    # Get the content of the progress.md file
    content = commit.tree / 'progress.md'
    content = content.data_stream.read().decode('utf-8')

    # Count the number of checked and unchecked functions
    checked = len(re.findall(r'\[x\]', content))
    unchecked = len(re.findall(r'\[ \]', content))

    progress.append((date, checked, unchecked))

progress = sorted(progress, key=lambda x: x[0])
date_range = pd.date_range(start=progress[0][0], end=progress[-1][0], freq='h')

new_progress = []
for date in date_range:
    checked = 0
    unchecked = 0
    for d, c, u in progress:
        if d.date() <= date.date():
            checked = c
            unchecked = u
    total = checked + unchecked
    new_progress.append((date, (checked * 100) / total, (unchecked * 100) / total))

progress_df = pd.DataFrame(new_progress, columns=['date', 'checked', 'unchecked'])

fig, ax = plt.subplots()

ax.plot(progress_df['date'], progress_df['checked'], label='Decompiled')

ax.xaxis.set_major_locator(mdates.MonthLocator())
ax.xaxis.set_major_formatter(mdates.DateFormatter('%b %Y'))
ax.xaxis.set_minor_locator(mdates.WeekdayLocator())
ax.yaxis.set_major_formatter(ticker.PercentFormatter())

total_progress = progress_df['checked'].iloc[-1]

decomped = progress[-1][1]
total = decomped + progress[-1][2]

plt.title('Percentage of the main executable decompiled (%.2f%%) (%d/%d)' % (total_progress, decomped, total))
plt.savefig('.github/assets/progress.png')