#!/usr/bin/env bash

CONFIGS=( "bashrc" "gitconfig" "gitconfig.user" "gitignore" )

echo "Installing Better Defaults..."

for i in "${CONFIGS[@]}"; do
    if [ -f "${HOME}/.${i}" ]; then

        echo ".${i} exists. Do you want to backup your .${i} and install?"
        echo "1 for backup and install"
        echo "2 to quit and do nothing"
        select yn in "Yes" "No"; do
            case $yn in
                Yes ) break;;
                No ) exit 1;;
            esac
        done

        # backup current
        echo "Backing up to ${HOME}/.${i}.old ..."
        mv "${HOME}/.${i}" "${HOME}/.${i}.old"
    fi

    # install bashrc
    echo "Installing .${i}"
    cp "../examples/${i}" "${HOME}/.${i}"
done

echo "Done"
echo "Please read and customize ~/.gitconfig.user"

exit 0
