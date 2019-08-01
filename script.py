import requests
import pathlib
import bs4
import re
import sys
from slugify import slugify

root_path = pathlib.Path('./sio2_archive')
root_path.mkdir(exist_ok=True)

URL = 'https://sio2.mimuw.edu.pl/'
s = requests.Session()
s.get(URL)

def get_data():
	return {
		'auth-username' : '',
		'auth-password' : '',
		'csrfmiddlewaretoken' : s.cookies['csrftoken'],
		'login_view-current_step' : 'auth'
	}

post_url = 'https://sio2.mimuw.edu.pl/c/oi26-2/account/login/?next=/c/oi26-2/'
s.post(post_url, data = get_data(), headers = {'Referer' : post_url})

soup = bs4.BeautifulSoup(s.get('https://sio2.mimuw.edu.pl/c/oi26-2/contest/').text, "html.parser")
contests = soup.find_all('a', 'fill-clickable')

def check_score(x):
	return x.strip() == '100'

for c in contests:
	name = slugify(c.text)
	print(f"Processing: {name}")

	cur_dir = root_path / name

	name = slugify(c.text)
	contest_url = URL + c['href']
	page = s.get(contest_url + 'submissions/')
	
	if 'Brak nadesłanych rozwiązań' in page.text:
		print(f"Brak submitów w konkursie {name}")
		continue
	submissions = bs4.BeautifulSoup(page.text, "html.parser").find(name="table", class_="table table-condensed submission").tbody
	submissions = submissions.find_all('tr')
	submissions = [submissions[i] for i in range(0, len(submissions), 2)]

	seen = set()
	for sub in submissions:
		score = sub.find(name='td', id=re.compile(r'.*score$')).text
		if not check_score(score): continue
		data = sub.find(name='td', id=re.compile(r'.*problem-instance$'))
		prob_name = re.search(r'(\(.*\))', data.text).group()[1:-1]
		sub_id = re.match(r'submission(\d+).*', data['id']).group(1)

		if prob_name in seen: continue
		seen.add(prob_name)

		code = cur_dir / (prob_name + '.cpp')
		if not cur_dir.exists():
			cur_dir.mkdir()
		with code.open('wb') as file:
			file.write(s.get(contest_url + 's/' + sub_id + '/download').content)
