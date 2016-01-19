# Author: Ahmer Malik
# Company: Techknox System
# Version: 0.1
# Description:This script is used create a kvm using VM-builder. Follow the link for understanding : https://www.howtoforge.com/creating-virtual-machines-for-xen-kvm-vmware-workstation-6-vmware-server-with-vmbuilder-on-ubuntu-8.10-p2

#!/bin/bash 

# Name of KVM you want to build
VM_NAME=python-dev
# Path of KVM, where to build
_PATH=scripted_kvms/$VM_NAME

mkdir -p $_PATH/mytemplates/libvirt/
cp /etc/vmbuilder/libvirt/* $_PATH/mytemplates/libvirt/
echo root 1000 > $_PATH/vmbuilder.partition
echo swap 500 >> $_PATH/vmbuilder.partition
echo /var 5000 >> $_PATH/vmbuilder.partition
echo passwd -e ahmer > $_PATH/boot.sh
echo apt-get update --apt-get install -qqy --force-yes openssh-server >> $_PATH/boot.sh
sudo chmod +x $_PATH/boot.sh
cd $_PATH

# Commands used to create the Ubuntu:Trusty KVM
vmbuilder kvm ubuntu --suite=trusty --flavour=virtual --arch=amd64 --mirror=http://de.archive.ubuntu.com/ubuntu -o --tmpfs=- --libvirt=qemu:///system --ip=192.168.7.2  --part=vmbuilder.partition --templates=mytemplates --user=ahmer --name=ahmer --pass=ahmer --addpkg=vim-nox --addpkg=unattended-upgrades --addpkg=acpid --addpkg=linux-image-generic --firstboot=/home/ahmer/Techknox/Make_Your_KVM_script/$_PATH/boot.sh --mem=512 --cpus=1 --hostname=$VM_NAME 
