find -name '*.cpp' -o -name '*.h' -exec sed -e 's/QtZeitgeist/QZeitgeist/g' -i {} \;
find -name '*.cpp' -o -name '*.h' -exec sed -e 's/QZeitgeist::init();//g' -i {} \;
