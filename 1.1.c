#include <stdio.h> 
#include<stdlib.h>
#include<string.h> 
#include <libxml/parser.h>  
#include <libxml/tree.h>
#include<unistd.h>
#include<fcntl.h>
#include<libxml/xpath.h>
int create_xml_domain( xmlNodePtr root_node)
{
    
	xmlNewProp(root_node, BAD_CAST "type", BAD_CAST "kvm");
	xmlNewProp(root_node, BAD_CAST "id", BAD_CAST "9");
	xmlNewProp(root_node, BAD_CAST "xmlns:qemu", BAD_CAST "http://libvirt.org/schemas/domain/qemu/1.0");
	  
}	  
	
int create_xml_name(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_name;
	flag_name=0;
	xmlChar *name;
	
	for(curNode=proot->children;curNode;curNode=curNode->next)
	{
	  if(xmlStrcasecmp(curNode->name,BAD_CAST"name")==0)
	  {
	  flag_name=1;
	  name=xmlNodeGetContent(curNode);
	  xmlNewChild(root_node,NULL, BAD_CAST "name",BAD_CAST (name)); 
	  }
	}
	if(flag_name==0)
      {
	  xmlNewChild(root_node,NULL, BAD_CAST "name",BAD_CAST "Win7_1_0");
	  }	
}

int create_xml_uuid(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_uuid;
	flag_uuid=0;
	xmlChar *uuid;
	
	for(curNode=proot->children;curNode;curNode=curNode->next)
	{
	  if(xmlStrcasecmp(curNode->name,BAD_CAST"uuid")==0)
	  {
	  flag_uuid=1;
	  uuid=xmlNodeGetContent(curNode);
	  xmlNewChild(root_node,NULL, BAD_CAST "name",BAD_CAST (uuid)); 
	  }
	}
	if(flag_uuid==0)
      {
	  xmlNewChild(root_node,NULL, BAD_CAST "uuid",BAD_CAST "16d574e8-5368-45f8-b389-64c9898641ad"); // create a child node
	  }	
}

int create_xml_memory(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_memory;
	flag_memory=0;
	xmlChar *mem;
	xmlNodePtr node=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"memory")==0)
                       
          {
		    flag_memory=1;
			//nodeName = (char *) curNode->name;  
			mem =xmlNodeGetContent(curNode);  
			node = xmlNewChild(root_node, NULL, BAD_CAST "memory", BAD_CAST (mem));//creat child node   
	        xmlNewProp(node, BAD_CAST "unit", BAD_CAST "KIB");
         }
    }	
    if(flag_memory==0)
    {
	node = xmlNewChild(root_node, NULL, BAD_CAST "memory", BAD_CAST "1048576");//creat child node   
	xmlNewProp(node, BAD_CAST "unit", BAD_CAST "KIB");
	
	}		 
}

 int create_xml_currentmemory(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_currentMemory;
	flag_currentMemory=0;
	xmlChar *currentMemory;
	xmlNodePtr node=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"currentMemory")==0)
                       
          {
		    flag_currentMemory=1;
			currentMemory = xmlNodeGetContent(curNode);  
			node = xmlNewChild(root_node, NULL, BAD_CAST "currentMemory", BAD_CAST (currentMemory));//creat child node   
	        xmlNewProp(node, BAD_CAST "unit", BAD_CAST "KIB");
         }
    }	
    if(flag_currentMemory==0)
    {
	node = xmlNewChild(root_node, NULL, BAD_CAST "currentMemory", BAD_CAST "1048576");//creat child node   
	xmlNewProp(node, BAD_CAST "unit", BAD_CAST "KIB");
	
	}		 
} 

int create_xml_blkiotune(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
	int flag_blkiotune;
	flag_blkiotune=0;
	xmlChar *weight;
	xmlNodePtr node=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"blkiotune")==0)
                       
          {
		    flag_blkiotune=1;
			weight = (char *) xmlNodeGetContent(curNode);  
			node=xmlNewChild(root_node,NULL, BAD_CAST "blkiotune",NULL); // create a child node
	        xmlNewChild(node,NULL, BAD_CAST "weight",BAD_CAST (weight));  
         }
    }	
    if(flag_blkiotune==0)
    {
	node=xmlNewChild(root_node,NULL, BAD_CAST "blkiotune",NULL); // create a child node
	xmlNewChild(node,NULL, BAD_CAST "weight",BAD_CAST "700"); 
	
	}	

}

int create_xml_vcpu(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
int flag_vcpu;
	flag_vcpu=0;
	xmlChar *cores;
	xmlNodePtr node=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"cpu")==0)
                       
          {
		    flag_vcpu=1;
			childNode=curNode->children;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"topology")==0)
			  {
			   cores =xmlGetProp(childNode,BAD_CAST"cores");  
		       node = xmlNewChild(root_node, NULL, BAD_CAST "vcpu", BAD_CAST (cores));//creat child node   
		       xmlNewProp(node, BAD_CAST "placement", BAD_CAST "static");
			  }
         }
    }	
    if(flag_vcpu==0)
    {
	node = xmlNewChild(root_node, NULL, BAD_CAST "vcpu", BAD_CAST "1");//creat child node   
	xmlNewProp(node, BAD_CAST "placement", BAD_CAST "static");
	
	}	
}

int create_xml_cputune(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
int flag_cputune;
	flag_cputune=0;
	xmlChar *shares,*period,*quota;
	xmlNodePtr node=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"cputune")==0)
                       
          {
		    flag_cputune=1; 
            node=xmlNewChild(root_node,NULL, BAD_CAST "cputune",NULL);
			childNode= curNode->children;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"shares")==0)
			  {
			   shares = (char *) xmlNodeGetContent(childNode);
			   xmlNewChild(node,NULL, BAD_CAST "shares",BAD_CAST (shares));
			  }
			childNode= childNode->next;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"period")==0)
			  {
			   period = (char *) xmlNodeGetContent(childNode);
			   xmlNewChild(node,NULL, BAD_CAST "period",BAD_CAST (period));
			  }
			childNode= childNode->next;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"quota")==0)
			  {
			   quota = (char *) xmlNodeGetContent(childNode);
			   xmlNewChild(node,NULL, BAD_CAST "quota",BAD_CAST (quota));
			  }
         }
    }	
    if(flag_cputune==0)
    {
	node=xmlNewChild(root_node,NULL, BAD_CAST "cputune",NULL); // create a child node
	xmlNewChild(node,NULL, BAD_CAST "shares",BAD_CAST "1000"); 
	xmlNewChild(node,NULL, BAD_CAST "period",BAD_CAST "1000000");
	xmlNewChild(node,NULL, BAD_CAST "quota",BAD_CAST "1000000");
	
	}
}

int create_xml_resource(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
int flag_resource;
	flag_resource=0;
	xmlChar *partition;
	xmlNodePtr node=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"resource")==0)
                       
          {
		    flag_resource=1; 
            node=xmlNewChild(root_node,NULL, BAD_CAST "resource",NULL);
			childNode= curNode->children;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"partition")==0)
			  {
			  partition = (char *) xmlNodeGetContent(childNode);
			   xmlNewChild(node,NULL, BAD_CAST "partition",BAD_CAST (partition));
			  }
			
         }
    }	
    if(flag_resource==0)
    {
	node=xmlNewChild(root_node,NULL, BAD_CAST "resource",NULL); // create a child node
	xmlNewChild(node,NULL, BAD_CAST "partition",BAD_CAST "/machine"); 
	
	}
}

int create_xml_os(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
int flag_os;
	flag_os=0;
	xmlChar *type,*boot,*arch,*machine;
	xmlNodePtr node=NULL,node1=NULL,node2=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"os")==0)
                       
          {
		    flag_os=1; 
            node=xmlNewChild(root_node,NULL, BAD_CAST "os",NULL);
			childNode= curNode->children;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"type")==0)
			  {
			   type =  xmlNodeGetContent(childNode);
			   node1=xmlNewChild(node,NULL, BAD_CAST "type",BAD_CAST (type));
			   arch =  xmlGetProp(childNode,BAD_CAST"arch");
			   xmlNewProp(node1, BAD_CAST "arch", BAD_CAST (arch));
			   machine = (char *)xmlGetProp(childNode,BAD_CAST"machine");
			   xmlNewProp(node1, BAD_CAST "machine", BAD_CAST (machine));
			  }
			childNode= childNode->next;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"boot")==0)
			  {
			   boot =  xmlGetProp(childNode,BAD_CAST"dev");
			   node1=xmlNewChild(node,NULL, BAD_CAST "boot",NULL);
			   xmlNewProp(node1, BAD_CAST "dev", BAD_CAST (boot));
			  }
			
         }
    }	
    if(flag_os==0)
    {
	node=xmlNewChild(root_node,NULL, BAD_CAST "os",NULL); // create a child node
	node1=xmlNewChild(node,NULL, BAD_CAST "type",BAD_CAST "hvm");
	xmlNewProp(node1, BAD_CAST "arch", BAD_CAST "x86_64");		
	xmlNewProp(node1, BAD_CAST "machine", BAD_CAST "pc-i440fx-2.5");		 
	node2= xmlNewChild(node,NULL, BAD_CAST "boot",NULL);
	xmlNewProp(node2, BAD_CAST "dev", BAD_CAST "hd");
	}
}
int create_xml_cpu(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
int flag_cpu;
	flag_cpu=0;
	xmlChar *sockets,*cores,*threads;
	xmlNodePtr node=NULL,node1=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"cpu")==0)
                       
          {
		    flag_cpu=1;
			
			node=xmlNewChild(root_node,NULL, BAD_CAST "cpu",NULL); // create a child node
			
			//xmlNewProp(node1, BAD_CAST "sockets", BAD_CAST "1");
			childNode= curNode->children;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"topology")==0)
			  {
			   node1=xmlNewChild(node,NULL, BAD_CAST "topology",NULL);
			   sockets=xmlGetProp(childNode,BAD_CAST"sockets");
			   xmlNewProp(node1, BAD_CAST "sockets", BAD_CAST (sockets));
			   cores =  xmlGetProp(childNode,BAD_CAST"cores");
			   xmlNewProp(node1, BAD_CAST "cores", BAD_CAST (cores));
			   threads=  xmlGetProp(childNode,BAD_CAST"threads");
			   xmlNewProp(node1, BAD_CAST "threads", BAD_CAST (threads));
			  }
			
         }
    }	
    if(flag_cpu==0)
    {
	node=xmlNewChild(root_node,NULL, BAD_CAST "cpu",NULL); // create a child node
	node1=xmlNewChild(node,NULL, BAD_CAST "topology",NULL);
	xmlNewProp(node1, BAD_CAST "sockets", BAD_CAST "1");
	xmlNewProp(node1, BAD_CAST "cores", BAD_CAST "1");
	xmlNewProp(node1, BAD_CAST "threads", BAD_CAST "1");
	
	}	
}

int create_xml_clock(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_clock;
	flag_clock=0;
    xmlChar *offset;
	xmlNodePtr node2=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"clock")==0)
                       
          {
		    flag_clock=1;
			node2=xmlNewChild(root_node,NULL, BAD_CAST "clock",NULL); // create a child node
			offset=xmlGetProp(curNode,BAD_CAST"offset");
			xmlNewProp(node2, BAD_CAST "offset", BAD_CAST (offset));
			
         }
    }	
    if(flag_clock==0)
    {
	node2=xmlNewChild(root_node,NULL, BAD_CAST "clock",NULL);
	xmlNewProp(node2, BAD_CAST "offset", BAD_CAST "localtime");

	
	}	
}

int create_xml_on_poweroff(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_on_poweroff;
	flag_on_poweroff=0;
	char *on_poweroff;
	
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"on_poweroff")==0)
                       
          {
		    flag_on_poweroff=1;
			on_poweroff= (char *) xmlNodeGetContent(curNode); 
			xmlNewChild(root_node,NULL, BAD_CAST "on_poweroff",BAD_CAST (on_poweroff));  // create a child node
			
			
         }
    }	
    if(flag_on_poweroff==0)
    {
	 xmlNewChild(root_node,NULL, BAD_CAST "on_poweroff",BAD_CAST "destroy"); 

	
	}	 
}

int create_xml_on_reboot(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_on_reboot;
	flag_on_reboot=0;
	char *on_reboot;
	
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"on_reboot")==0)
                       
          {
		    flag_on_reboot=1;
			on_reboot= (char *) xmlNodeGetContent(curNode); 
			xmlNewChild(root_node,NULL, BAD_CAST "on_reboot",BAD_CAST (on_reboot));  // create a child node
			
			
         }
    }	
    if(flag_on_reboot==0)
    {
	 xmlNewChild(root_node,NULL, BAD_CAST "on_reboot",BAD_CAST "restart"); 

	
	}	 
}

int create_xml_on_crash(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
int flag_on_crash;
	flag_on_crash=0;
	char *on_crash;
	
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"on_crash")==0)
                       
          {
		    flag_on_crash=1;
			on_crash= (char *) xmlNodeGetContent(curNode); 
			xmlNewChild(root_node,NULL, BAD_CAST "on_crash",BAD_CAST (on_crash));  // create a child node
			
			
         }
    }	
    if(flag_on_crash==0)
    {
	 xmlNewChild(root_node,NULL, BAD_CAST "on_crash",BAD_CAST "destroy"); // create a child node		

	
	}	 
}	

int create_xml_pm(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
 int flag_pm;
	flag_pm=0;
	char *enabled;
	xmlNodePtr node=NULL,node1=NULL,node2=NULL;
    for(curNode=proot->children;curNode;curNode=curNode->next)
    {
      if(xmlStrcasecmp(curNode->name,BAD_CAST"pm")==0)
                       
          {
		    flag_pm=1; 
            node=xmlNewChild(root_node,NULL, BAD_CAST "pm",NULL);
			childNode= curNode->children;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"suspend-to-mem")==0)
			  {
			   node1=xmlNewChild(node,NULL, BAD_CAST "suspend-to-mem",NULL);
			   enabled =  xmlGetProp(childNode,BAD_CAST"enabled");
			   xmlNewProp(node1, BAD_CAST "enabled", BAD_CAST (enabled));
			  }
			childNode= childNode->next;
			if(xmlStrcasecmp(childNode->name,BAD_CAST"suspend-to-disk")==0)
			  {
			   node1=xmlNewChild(node,NULL, BAD_CAST "suspend-to-disk",NULL);
			   enabled =  xmlGetProp(childNode,BAD_CAST"enabled");
			   xmlNewProp(node1, BAD_CAST "enabled", BAD_CAST (enabled));
			  }
			
         }
    }	
    if(flag_pm==0)
    {
	node=xmlNewChild(root_node,NULL, BAD_CAST "pm",NULL); // create a child node
	node1=xmlNewChild(node,NULL, BAD_CAST "suspend-to-mem",NULL);
	xmlNewProp(node1, BAD_CAST "enabled", BAD_CAST "no");
	node2=xmlNewChild(node,NULL, BAD_CAST "suspend-to-disk",NULL);
	xmlNewProp(node2, BAD_CAST "enabled", BAD_CAST "yes");
	}
}


int create_xml_devices(xmlNodePtr root_node, xmlNodePtr proot,xmlNodePtr curNode,xmlNodePtr childNode)
{
	int flag_devices;
	flag_devices=0;
	xmlNodePtr child_node=NULL,grand_node=NULL;
	xmlNodePtr node=NULL,node1=NULL,node2=NULL;
	for(curNode=proot->children;curNode;curNode=curNode->next)
 { 
	if(xmlStrcasecmp(curNode->name,BAD_CAST"devices")==0)
                       
  {
    flag_devices=1;
	child_node=xmlNewChild(root_node,NULL, BAD_CAST "devices",NULL);
	create_xml_devices_emulator( curNode,child_node,childNode);
    create_xml_devices_disk( curNode,child_node,childNode);
	create_xml_devices_controller(curNode, child_node,childNode);
	create_xml_devices_interface( curNode,child_node,childNode);
	create_xml_devices_serial( curNode, child_node, childNode);
	create_xml_devices_console( curNode, child_node, childNode);
	create_xml_devices_channel( curNode, child_node,childNode);
	create_xml_devices_input(curNode,child_node, childNode);
	create_xml_devices_graphics( curNode, child_node, childNode);
	create_xml_devices_sound( curNode, child_node, childNode);
	create_xml_devices_video( curNode, child_node, childNode);
	create_xml_devices_memballoon( curNode,child_node, childNode);
 }
 
 }	
 if(flag_devices==0)
	{   
	    
	    child_node=xmlNewChild(root_node,NULL, BAD_CAST "devices",NULL);
		xmlNewChild(child_node,NULL, BAD_CAST "emulator",BAD_CAST "/usr/bin/qemu-system-x86_64");
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "disk",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "file");
		xmlNewProp(grand_node, BAD_CAST "device", BAD_CAST "disk");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "driver",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "qemu");
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "qcow2");
		xmlNewProp(node1, BAD_CAST "cache", BAD_CAST "writeback");
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "file", BAD_CAST "/opt/lessons/Win7_1.img");
		node=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node, BAD_CAST "dev", BAD_CAST "hda");
		xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ide");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST"ide0-0-0");
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "drive");
		xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "target", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "unit", BAD_CAST "0");
		
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "disk",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "file");
		xmlNewProp(grand_node, BAD_CAST "device", BAD_CAST "disk");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "driver",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "qemu");
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "qcow2");
		xmlNewProp(node1, BAD_CAST "cache", BAD_CAST "writeback");
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "file", BAD_CAST "/opt/data/hugedisk/Win7_1_0_share.add");
		node=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node, BAD_CAST "dev", BAD_CAST "hdb");
		xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ide");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST"ide0-0-1");
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "drive");
		xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "target", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "unit", BAD_CAST "1");
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "usb");
		xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
			
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "usb0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x01");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x02");
			
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
		xmlNewProp(grand_node, BAD_CAST "model", BAD_CAST "pci-root");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "pci.0");

			
	   
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "ide");
		xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "ide.0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x01");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x01");
			
		   
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "virtio-serial");
		xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "virtio-serial0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x05");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
		
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "interface",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "bridge");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "mac",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "address", BAD_CAST "52:54:00:24:f0:31");
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "bridge", BAD_CAST "br0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "dev", BAD_CAST "vnet0");
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "model",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "virtio");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "net0");
		
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x03");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
			
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "serial",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pty");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "path", BAD_CAST "/dev/pts/6");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "port", BAD_CAST "0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "serial0");

		  
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "serial",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pty");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "path", BAD_CAST "/dev/pts/7");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "port", BAD_CAST "1");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "serial1");
			
			
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "console",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pty");
		xmlNewProp(grand_node, BAD_CAST "tty", BAD_CAST "/dev/pts/6");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "path", BAD_CAST "/dev/pts/6");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "serial");
		xmlNewProp(node1, BAD_CAST "port", BAD_CAST "0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "serial0");       


		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "channel",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "spicevmc");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "virtio");
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "com.redhat.spice.0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "channel0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "virtio-serial");
		xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "port", BAD_CAST "1");


		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "channel",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "spiceport");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "channel", BAD_CAST "webcam");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "virtio");
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "com.redhat.spice.webcam");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "channel");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "virtio-serial");
		xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "port", BAD_CAST "2");

		   
		node=xmlNewChild(child_node,NULL, BAD_CAST "input",NULL); // create a child node
		xmlNewProp(node, BAD_CAST "type", BAD_CAST "mouse");
		xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ps2");
			
		node=xmlNewChild(child_node,NULL, BAD_CAST "input",NULL); // create a child node
		xmlNewProp(node, BAD_CAST "type", BAD_CAST "keyboard");
		xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ps2");
			
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "graphics",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "spice");
		xmlNewProp(grand_node, BAD_CAST "port", BAD_CAST "5900");
		xmlNewProp(grand_node, BAD_CAST "autoport", BAD_CAST "yes");
		xmlNewProp(grand_node, BAD_CAST "listen", BAD_CAST "0.0.0.0");
		node1=xmlNewChild(grand_node,NULL,BAD_CAST "listen",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "address" );
		xmlNewProp(node1, BAD_CAST "address", BAD_CAST "0.0.0.0" );

		 
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "graphics",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "vnc");
		xmlNewProp(grand_node, BAD_CAST "port", BAD_CAST "5901");
		xmlNewProp(grand_node, BAD_CAST "autoport", BAD_CAST "yes");
		xmlNewProp(grand_node, BAD_CAST "listen", BAD_CAST "0.0.0.0");
		node1=xmlNewChild(grand_node,NULL,BAD_CAST "listen",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "address" );
		xmlNewProp(node1, BAD_CAST "address", BAD_CAST "0.0.0.0" );	
		
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "sound",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "model", BAD_CAST "ich6");
		node1=xmlNewChild(grand_node,NULL,BAD_CAST "code",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "micro" );
		node1=xmlNewChild(grand_node,NULL,BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "sound0" );
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x04");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
		
		
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "video",NULL); 
		node=xmlNewChild(grand_node,NULL, BAD_CAST "model",NULL); 
		xmlNewProp(node, BAD_CAST "type", BAD_CAST "qxl");
		xmlNewProp(node, BAD_CAST "ram", BAD_CAST "65536");
		xmlNewProp(node, BAD_CAST "heads", BAD_CAST "1");
		node1=xmlNewChild(node,NULL, BAD_CAST "acceleration",NULL); 
		xmlNewProp(node1, BAD_CAST "accel3d", BAD_CAST "no");
		xmlNewProp(node1, BAD_CAST "accel2d", BAD_CAST "yes");
			
		node=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); 
		xmlNewProp(node, BAD_CAST "name", BAD_CAST "video0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x02");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
		
		
		
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "memballoon",NULL); 
		xmlNewProp(grand_node, BAD_CAST "model", BAD_CAST "virtio");
		node=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); 
		xmlNewProp(node, BAD_CAST "name", BAD_CAST "balloono");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x08");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
	
	}
}

int create_xml_devices_emulator(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
int flag_emulator;
	flag_emulator=0;
	char *emulator;
	
     for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
      if(xmlStrcasecmp(childNode->name,BAD_CAST "emulator")==0)
                       
          { 
		   
		    flag_emulator=1;    
			emulator = (char *) xmlNodeGetContent(curNode); 
			xmlNewChild(child_node,NULL, BAD_CAST "emulator",(emulator));

         }
	 	 
	  }
    if(flag_emulator==0)
    {
	
	xmlNewChild(child_node,NULL, BAD_CAST "emulator",BAD_CAST "/usr/bin/qemu-system-x86_64");
	}	
	
	
  }	
 
int  create_xml_devices_disk(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
 int flag_disk;
	flag_disk=0;
	char *type1,*device;
	xmlNodePtr grand_node=NULL;
	xmlNodePtr node=NULL,node1=NULL,node2=NULL,node3=NULL,grandNode=NULL;
 for(childNode=curNode->children;childNode;childNode=childNode->next)
	{
      if(xmlStrcasecmp(childNode->name,BAD_CAST "disk")==0)
                       
          {
		    flag_disk=1;
			
			node3=xmlNewChild(child_node,NULL, BAD_CAST "disk",NULL); // create a child node
			type1=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node3, BAD_CAST "type", BAD_CAST (type1));
			device=xmlGetProp(childNode,BAD_CAST "device");
			xmlNewProp(node3, BAD_CAST "device", BAD_CAST (device));
			 create_xml_devices_disk_(curNode, grandNode, node3, childNode);
		 }
	}
if(flag_disk==0)
		{
			grand_node=xmlNewChild(child_node,NULL, BAD_CAST "disk",NULL); // create a child node
			xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "file");
			xmlNewProp(grand_node, BAD_CAST "device", BAD_CAST "disk");
			node1=xmlNewChild(grand_node,NULL, BAD_CAST "driver",NULL); // create a child node
			xmlNewProp(node1, BAD_CAST "name", BAD_CAST "qemu");
			xmlNewProp(node1, BAD_CAST "type", BAD_CAST "qcow2");
			xmlNewProp(node1, BAD_CAST "cache", BAD_CAST "writeback");
			node2=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
			xmlNewProp(node2, BAD_CAST "file", BAD_CAST "/opt/lessons/Win7_1.img");
			node=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
			xmlNewProp(node, BAD_CAST "dev", BAD_CAST "hda");
			xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ide");
			node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
			xmlNewProp(node1, BAD_CAST "name", BAD_CAST "ide0-0-0");
			node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
			xmlNewProp(node2, BAD_CAST "type", BAD_CAST "drive");
			xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
			xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
			xmlNewProp(node2, BAD_CAST "target", BAD_CAST "0");
			xmlNewProp(node2, BAD_CAST "unit", BAD_CAST "0");
			
			grand_node=xmlNewChild(child_node,NULL, BAD_CAST "disk",NULL); // create a child node
			xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "file");
			xmlNewProp(grand_node, BAD_CAST "device", BAD_CAST "disk");
			node1=xmlNewChild(grand_node,NULL, BAD_CAST "driver",NULL); // create a child node
			xmlNewProp(node1, BAD_CAST "name", BAD_CAST "qemu");
			xmlNewProp(node1, BAD_CAST "type", BAD_CAST "qcow2");
			xmlNewProp(node1, BAD_CAST "cache", BAD_CAST "writeback");
			node2=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
			xmlNewProp(node2, BAD_CAST "file", BAD_CAST "/opt/data/hugedisk/Win7_1_0_share.add");
			node=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
			xmlNewProp(node, BAD_CAST "dev", BAD_CAST "hdb");
			xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ide");
			node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
			xmlNewProp(node1, BAD_CAST "name", BAD_CAST "ide0-0-1");
			node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
			xmlNewProp(node2, BAD_CAST "type", BAD_CAST "drive");
			xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
			xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
			xmlNewProp(node2, BAD_CAST "target", BAD_CAST "0");
			xmlNewProp(node2, BAD_CAST "unit", BAD_CAST "1");
		}
   	

}

int  create_xml_devices_disk_(xmlNodePtr curNode,xmlNodePtr grandNode,xmlNodePtr node3,xmlNodePtr childNode)
{
xmlNodePtr node=NULL,node1=NULL,node2=NULL;
char *name2,*type2,*cache,*file,*dev,*bus,*name3,*type3,*controller,*bus1,*target,*unit,*domain,*slot,*function;
for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "driver")==0)
			  {
			   printf("---862---");
			   node1=xmlNewChild(node3,NULL, BAD_CAST "driver",NULL);
			   name2=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node1, BAD_CAST "name", BAD_CAST (name2));
			   type2 =  xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node1, BAD_CAST "type", BAD_CAST (type2));
			   cache=  xmlGetProp(grandNode,BAD_CAST "cache");
			   xmlNewProp(node1, BAD_CAST "cache", BAD_CAST (cache));
			  }
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "source")==0)
			  {
			   node1=xmlNewChild(node3,NULL, BAD_CAST "source",NULL);
			   file=xmlGetProp(grandNode,BAD_CAST "file");
			   xmlNewProp(node1, BAD_CAST "file", BAD_CAST (file));
			  }
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "target")==0)
			  {
			   node1=xmlNewChild(node3,NULL, BAD_CAST "target",NULL);
			   dev=xmlGetProp(grandNode,BAD_CAST "dev");
			   xmlNewProp(node1, BAD_CAST "dev", BAD_CAST (dev));
			   bus=xmlGetProp(grandNode,BAD_CAST "bus");
			   xmlNewProp(node1, BAD_CAST "bus", BAD_CAST (bus));
			 if(!strcmp(bus,"ide"))
			  {
			     
				grandNode=grandNode->next;
			   if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			   {
			  
			    node2=xmlNewChild(node3,NULL, BAD_CAST "alias",NULL);
			    name3=xmlGetProp(grandNode,BAD_CAST "name");
			    xmlNewProp(node2, BAD_CAST "name", BAD_CAST (name3));
			    
			   } 
			  
			   grandNode=grandNode->next;
			   if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			   {
			    node1=xmlNewChild(node3,NULL, BAD_CAST "address",NULL);
			    type3=xmlGetProp(grandNode,BAD_CAST "type");
				xmlNewProp(node1, BAD_CAST "type", BAD_CAST (type3));
				controller=xmlGetProp(grandNode,BAD_CAST "controller");
				xmlNewProp(node1, BAD_CAST "controller", BAD_CAST (controller));
				bus1=xmlGetProp(grandNode,BAD_CAST "bus");
				xmlNewProp(node1, BAD_CAST "bus", BAD_CAST (bus1));
				target=xmlGetProp(grandNode,BAD_CAST "target");
				xmlNewProp(node1, BAD_CAST "target", BAD_CAST (target));
				unit=xmlGetProp(grandNode,BAD_CAST "unit");
				xmlNewProp(node1, BAD_CAST "unit", BAD_CAST (unit));
			   }
			  }
			   
			 else if(!strcmp(bus,"virtio"))
			  {
			  
				node2=xmlNewChild(node3,NULL, BAD_CAST "readonly",NULL);
			    grandNode=(grandNode->next)->next;
			    if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
				{
				
				 
				 node1=xmlNewChild(node3,NULL, BAD_CAST "alias",NULL);
			     name3=xmlGetProp(grandNode,BAD_CAST "name");
			     xmlNewProp(node1, BAD_CAST "name", BAD_CAST (name3));
				}
				grandNode=grandNode->next;
				
				if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			   {
			   printf("grandNode->name:%s",grandNode->name);
			    node1=xmlNewChild(node3,NULL, BAD_CAST "address",NULL);
			    type3=xmlGetProp(grandNode,BAD_CAST "type");
				xmlNewProp(node1, BAD_CAST "type", BAD_CAST (type3));
				domain=xmlGetProp(grandNode,BAD_CAST "domain");
				xmlNewProp(node1, BAD_CAST "domain", BAD_CAST (domain));
				bus1=xmlGetProp(grandNode,BAD_CAST "bus");
				xmlNewProp(node1, BAD_CAST "bus", BAD_CAST (bus1));
				slot=xmlGetProp(grandNode,BAD_CAST "slot");
				xmlNewProp(node1, BAD_CAST "slot", BAD_CAST (slot));
				function=xmlGetProp(grandNode,BAD_CAST "function");
				xmlNewProp(node1, BAD_CAST "function", BAD_CAST (function));
			   }
			   
			  } 
			   }
			} 
}


int  create_xml_devices_controller(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
 int flag_controller;
	flag_controller=0;
	char *type4,*index;
	xmlNodePtr grand_node=NULL;
	xmlNodePtr node=NULL,node1=NULL,node2=NULL,node3=NULL,grandNode=NULL;
	 for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	  
	 
      if(xmlStrcasecmp(childNode->name,BAD_CAST "controller")==0)
                       
          { 
		    flag_controller=1;    
			node2=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
			type4=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node2, BAD_CAST "type", BAD_CAST (type4));
			index=xmlGetProp(childNode,BAD_CAST "index");
			xmlNewProp(node2, BAD_CAST "index", BAD_CAST (index));	
			create_xml_devices_controller_(curNode, grandNode, node2, childNode);
		  }
	  }	 
if(flag_controller==0)
    {
	
	grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
	xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "usb");
	xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
		
	node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
	xmlNewProp(node1, BAD_CAST "name", BAD_CAST "usb0");
		
	node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
	xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
	xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
	xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
	xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x01");
	xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x02");
		
	grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
	xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pci");
	xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
	xmlNewProp(grand_node, BAD_CAST "model", BAD_CAST "pci-root");
	node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
	xmlNewProp(node1, BAD_CAST "name", BAD_CAST "pci.0");

        
   
    grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
	xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "ide");
	xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
	node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
	xmlNewProp(node1, BAD_CAST "name", BAD_CAST "ide.0");
		
	node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
	xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
	xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
	xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
	xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x01");
	xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x01");
		
       
    grand_node=xmlNewChild(child_node,NULL, BAD_CAST "controller",NULL); // create a child node
	xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "virtio-serial");
	xmlNewProp(grand_node, BAD_CAST "index", BAD_CAST "0");
	node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
	xmlNewProp(node1, BAD_CAST "name", BAD_CAST "virtio-serial0");
		
	node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
	xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
	xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
	xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
	xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x05");
	xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
    }	  
}	
	
	
int  create_xml_devices_controller_(xmlNodePtr curNode,xmlNodePtr grandNode,xmlNodePtr node2,xmlNodePtr childNode)
{
xmlNodePtr node=NULL,node1=NULL;
char *name4,*type5,	*domain1,*bus2,*slot1,*function1;
for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node1=xmlNewChild(node2,NULL, BAD_CAST "alias",NULL);
			   name4=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node1, BAD_CAST "name", BAD_CAST (name4));
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			  {
			  
			   node1=xmlNewChild(node2,NULL, BAD_CAST "address",NULL);
			   type5=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node1, BAD_CAST "type", BAD_CAST (type5));
			   domain1=xmlGetProp(grandNode,BAD_CAST "domain");
			   xmlNewProp(node1, BAD_CAST "domain", BAD_CAST (domain1));
			   bus2=xmlGetProp(grandNode,BAD_CAST "bus");
			   xmlNewProp(node1, BAD_CAST "bus", BAD_CAST (bus2));
			   slot1=xmlGetProp(grandNode,BAD_CAST "slot");
			   xmlNewProp(node1, BAD_CAST "slot", BAD_CAST (slot1));
			   function1=xmlGetProp(grandNode,BAD_CAST "function");
			   xmlNewProp(node1, BAD_CAST "function", BAD_CAST (function1));
			  } 
			}
}
	

int  create_xml_devices_interface(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
    int flag_interface;
	flag_interface=0;
	char *type7;
	xmlNodePtr grand_node=NULL,node4=NULL;
    xmlNodePtr node=NULL,node1=NULL,node2=NULL,node3=NULL,grandNode=NULL;
for(childNode=curNode->children;childNode;childNode=childNode->next)
      {
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "interface")==0)
                       
          {
		    flag_interface=1;
			node4=xmlNewChild(child_node,NULL, BAD_CAST "interface",NULL); // create a child node
			type7=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node4, BAD_CAST "type", BAD_CAST (type7));
			create_xml_devices_interface_( curNode, grandNode, node4, childNode);
		  }	
	  }	 
if(flag_interface==0)
		{	
			
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "interface",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "bridge");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "mac",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "address", BAD_CAST "52:54:00:24:f0:31");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "bridge", BAD_CAST "br0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "dev", BAD_CAST "vnet0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "model",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "virtio");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "net0");
			
		
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x03");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
		}		  

	
}	
	
int  create_xml_devices_interface_(xmlNodePtr curNode,xmlNodePtr grandNode,xmlNodePtr node4,xmlNodePtr childNode)
{
xmlNodePtr node=NULL,node1=NULL,node2=NULL;
char *address3,*bridge1,*dev1,*type7,*name6,*type8,*domain2,*bus3,*slot2,*function2;

 for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "mac")==0)
			  {
			  
		       node1=xmlNewChild(node4,NULL, BAD_CAST "mac",NULL);
			   address3=xmlGetProp(grandNode,BAD_CAST "address");
			   xmlNewProp(node1, BAD_CAST "address", BAD_CAST (address3));
			  }
			
			 if(xmlStrcasecmp(grandNode->name,BAD_CAST "source")==0)
			  {
			  
			   node2=xmlNewChild(node4,NULL, BAD_CAST "source",NULL);
			   bridge1=xmlGetProp(grandNode,BAD_CAST "bridge");
			   xmlNewProp(node2, BAD_CAST "bridge", BAD_CAST (bridge1));
			  } 
			  if(xmlStrcasecmp(grandNode->name,BAD_CAST"target")==0)
			  {
			   node1=xmlNewChild(node4,NULL, BAD_CAST "target",NULL);
			   dev1=xmlGetProp(grandNode,BAD_CAST"dev");
			   xmlNewProp(node1, BAD_CAST "dev", BAD_CAST (dev1));
			  } 
			if(xmlStrcasecmp(grandNode->name,BAD_CAST"model")==0)
			  {
			   node1=xmlNewChild(node4,NULL, BAD_CAST "model",NULL);
			   type7=xmlGetProp(grandNode,BAD_CAST"type");
			   xmlNewProp(node1, BAD_CAST "type", BAD_CAST (type7));
			  }   
			if(xmlStrcasecmp(grandNode->name,BAD_CAST"alias")==0)
			  {
			   node1=xmlNewChild(node4,NULL, BAD_CAST "alias",NULL);
			   name6=xmlGetProp(grandNode,BAD_CAST"name");
			   xmlNewProp(node1, BAD_CAST "name", BAD_CAST (name6));
			  }  
			 if(xmlStrcasecmp(grandNode->name,BAD_CAST"address")==0)
			  {
			 	
			   node1=xmlNewChild(node4,NULL, BAD_CAST "address",NULL);
			   type8=xmlGetProp(grandNode,BAD_CAST"type");
			   xmlNewProp(node1, BAD_CAST "type", BAD_CAST (type8));
			   domain2=xmlGetProp(grandNode,BAD_CAST"domain");
			   xmlNewProp(node1, BAD_CAST "domain", BAD_CAST (domain2));
			   bus3=xmlGetProp(grandNode,BAD_CAST"bus");
			   xmlNewProp(node1, BAD_CAST "bus", BAD_CAST (bus3));
			   slot2=xmlGetProp(grandNode,BAD_CAST"slot");
			   xmlNewProp(node1, BAD_CAST "slot", BAD_CAST (slot2));
			   function2=xmlGetProp(grandNode,BAD_CAST"function");
			   xmlNewProp(node1, BAD_CAST "function", BAD_CAST (function2));
			   
			  }
			}
	
}	

int  create_xml_devices_serial(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
    int flag_serial;
	flag_serial=0;
	char *type9;
	xmlNodePtr grand_node=NULL,node5=NULL;
    xmlNodePtr node=NULL,node1=NULL,grandNode=NULL;
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	  
       if(xmlStrcasecmp(childNode->name,BAD_CAST "serial")==0)
                       
          {
		    
		    flag_serial=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "serial",NULL); // create a child node
			type9=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node5, BAD_CAST "type", BAD_CAST (type9));
			create_xml_serial_( curNode, grandNode, node5, childNode);
	      }
	  }	  
	if(flag_serial==0)
	{
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "serial",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pty");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "path", BAD_CAST "/dev/pts/6");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "port", BAD_CAST "0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "serial0");
   
	
	}  
	
	
}


int create_xml_serial_(xmlNodePtr curNode,xmlNodePtr grandNode,xmlNodePtr node5,xmlNodePtr childNode)
{
xmlNodePtr node8=NULL;
char *path,*port,*dev1,*name8;

		 for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "source")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "source",NULL);
			   path=xmlGetProp(grandNode,BAD_CAST "path");
			   xmlNewProp(node8, BAD_CAST "path", BAD_CAST (path));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "target")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "target",NULL);
			   port=xmlGetProp(grandNode,BAD_CAST "port");
			   xmlNewProp(node8, BAD_CAST "port", BAD_CAST (port));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "alias",NULL);
			   name8=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node8, BAD_CAST "name", BAD_CAST (name8));
			  
			  }  
			
			}

}


int  create_xml_devices_console(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
    int flag_console;
	flag_console=0;
	char *type10,*tty;
	xmlNodePtr grand_node=NULL,node6=NULL;
    xmlNodePtr node1=NULL,grandNode=NULL;;
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "console")==0)
                       
          {
		   
		    flag_console=1;
			node6=xmlNewChild(child_node,NULL, BAD_CAST "console",NULL); // create a child node
			type10=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node6, BAD_CAST "type", BAD_CAST (type10));
		    tty=xmlGetProp(childNode,BAD_CAST "tty");
			xmlNewProp(node6, BAD_CAST "tty", BAD_CAST (tty));
			create_xml_console_(curNode, grandNode, node6,childNode);
		  }
       }
    if(flag_console==0)
	{
	
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "console",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "pty");
		xmlNewProp(grand_node, BAD_CAST "tty", BAD_CAST "/dev/pts/6");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "source",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "path", BAD_CAST "/dev/pts/6");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "serial");
		xmlNewProp(node1, BAD_CAST "port", BAD_CAST "0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "serial0");      
	}	   
	
}	

int create_xml_console_(xmlNodePtr curNode,xmlNodePtr grandNode,xmlNodePtr node6,xmlNodePtr childNode)
{
xmlNodePtr node8=NULL;
char *path1,*type11,*port1,*name9;
for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "source")==0)
			  {
			   node8=xmlNewChild(node6,NULL, BAD_CAST "source",NULL);
			   path1=xmlGetProp(grandNode,BAD_CAST "path");
			   xmlNewProp(node8, BAD_CAST "path", BAD_CAST (path1));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "target")==0)
			  {
			   node8=xmlNewChild(node6,NULL, BAD_CAST "target",NULL);
			   type11=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type11));
			   port1=xmlGetProp(grandNode,BAD_CAST "port");
			   xmlNewProp(node8, BAD_CAST "port", BAD_CAST (port1));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node8=xmlNewChild(node6,NULL, BAD_CAST "alias",NULL);
			   name9=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node8, BAD_CAST "name", BAD_CAST (name9));
			  
			  }  
			
			}
}


int  create_xml_devices_channel(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
    int flag_channel;
	flag_channel=0;
	char *type9,*tty;
	xmlNodePtr grand_node=NULL,node5=NULL;
    xmlNodePtr node1=NULL,node2=NULL,grandNode=NULL;
  
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "channel")==0)
                       
          {
		   
		    flag_channel=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "channel",NULL); // create a child node
			type9=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node5, BAD_CAST "type", BAD_CAST (type9));
			create_xml_channel_( curNode, grandNode, node5, childNode);
          }
       }		
if(flag_channel==0)
	{
	
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "channel",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "spicevmc");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "target",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "virtio");
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "com.redhat.spice.0");
		node1=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "name", BAD_CAST "channel0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "virtio-serial");
		xmlNewProp(node2, BAD_CAST "controller", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0");
		xmlNewProp(node2, BAD_CAST "port", BAD_CAST "1");

	}	   
}
int create_xml_channel_(xmlNodePtr curNode,xmlNodePtr grandNode,xmlNodePtr node5,xmlNodePtr childNode)
{
  xmlNodePtr node8=NULL;
 char *type,*name,*controller,*port,*bus;  
 for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "target")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "target",NULL);
			   type=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			   
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "alias",NULL);
			   name=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node8, BAD_CAST "name", BAD_CAST (name));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "address",NULL);
			   type=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			   controller=xmlGetProp(grandNode,BAD_CAST "controller");
			   xmlNewProp(node8, BAD_CAST "controller", BAD_CAST (controller));
			   bus=xmlGetProp(grandNode,BAD_CAST "bus");
			   xmlNewProp(node8, BAD_CAST "bus", BAD_CAST (bus));
			   port=xmlGetProp(grandNode,BAD_CAST "port");
			   xmlNewProp(node8, BAD_CAST "port", BAD_CAST (port));
			  
			  }  
			
			}
}

int  create_xml_devices_input(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
int flag_input;
	flag_input=0;
	char *type9,*bus;
    xmlNodePtr node5=NULL,node=NULL;
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "input")==0)
                       
          {
		   
		    flag_input=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "input",NULL); // create a child node
			type9=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node5, BAD_CAST "type", BAD_CAST (type9));
		    bus=xmlGetProp(childNode,BAD_CAST "bus");
			xmlNewProp(node5, BAD_CAST "bus", BAD_CAST (bus));
		
		  }	
        }		
	if(flag_input==0)
	{
		node=xmlNewChild(child_node,NULL, BAD_CAST "input",NULL); // create a child node
		xmlNewProp(node, BAD_CAST "type", BAD_CAST "mouse");
		xmlNewProp(node, BAD_CAST "bus", BAD_CAST "ps2");
	}

}

int  create_xml_devices_graphics(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
int flag_graphics;
	flag_graphics=0;
	xmlChar *type9,*port,*autoport,*listen;
	xmlNodePtr node1=NULL,node5=NULL,grand_node=NULL,grandNode=NULL;
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "graphics")==0)
                       
          {
		   
		    flag_graphics=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "graphics",NULL); // create a child node
			type9=xmlGetProp(childNode,BAD_CAST "type");
			xmlNewProp(node5, BAD_CAST "type", BAD_CAST (type9));
			port=xmlGetProp(childNode,BAD_CAST "port");
			xmlNewProp(node5, BAD_CAST "port", BAD_CAST (port));
			autoport=xmlGetProp(childNode,BAD_CAST "autoport");
			xmlNewProp(node5, BAD_CAST "autoport", BAD_CAST (autoport));
			listen=xmlGetProp(childNode,BAD_CAST "listen");
			xmlNewProp(node5, BAD_CAST "listen", BAD_CAST (listen));
			create_xml_devices_graphics_( grandNode, node5, childNode);
		  }
	  }
	  
if(flag_graphics==0)
	{
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "graphics",NULL); // create a child node
		xmlNewProp(grand_node, BAD_CAST "type", BAD_CAST "spice");
		xmlNewProp(grand_node, BAD_CAST "port", BAD_CAST "5900");
		xmlNewProp(grand_node, BAD_CAST "autoport", BAD_CAST "yes");
		xmlNewProp(grand_node, BAD_CAST "listen", BAD_CAST "0.0.0.0");
		node1=xmlNewChild(grand_node,NULL,BAD_CAST "listen",NULL); // create a child node
		xmlNewProp(node1, BAD_CAST "type", BAD_CAST "address" );
		xmlNewProp(node1, BAD_CAST "address", BAD_CAST "0.0.0.0" );
	}	  
}	  

int  create_xml_devices_graphics_(xmlNodePtr grandNode,xmlNodePtr node5,xmlNodePtr childNode)
{
xmlNodePtr node8=NULL;
char *type,*address;
for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "listen")==0)
			  {
			  node8=xmlNewChild(node5,NULL, BAD_CAST "listen",NULL);
			  type=xmlGetProp(grandNode,BAD_CAST "type");
			  xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			  address=xmlGetProp(grandNode,BAD_CAST "address");
			  xmlNewProp(node8, BAD_CAST "address", BAD_CAST (address));
			  
			  }
			}
}

int  create_xml_devices_sound(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
int flag_sound;
	flag_sound=0;
	xmlChar *model;
	xmlNodePtr node1=NULL,node2=NULL,node5=NULL,grand_node=NULL,grandNode=NULL;
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	
       if(xmlStrcasecmp(childNode->name,BAD_CAST "sound")==0)
                       
          {
		    flag_sound=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "sound",NULL); // create a child node
			model=xmlGetProp(childNode,BAD_CAST "model");
			xmlNewProp(node5, BAD_CAST "model", BAD_CAST (model));
			create_xml_devices_sound_( grandNode,node5, childNode);
		 }
       }		 
 if(flag_sound==0)
	{
			grand_node=xmlNewChild(child_node,NULL, BAD_CAST "sound",NULL); // create a child node
			xmlNewProp(grand_node, BAD_CAST "model", BAD_CAST "ich6");
			node1=xmlNewChild(grand_node,NULL,BAD_CAST "code",NULL); // create a child node
			xmlNewProp(node1, BAD_CAST "type", BAD_CAST "micro" );
			node1=xmlNewChild(grand_node,NULL,BAD_CAST "alias",NULL); // create a child node
			xmlNewProp(node1, BAD_CAST "name", BAD_CAST "sound0" );
				
			node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
			xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
			xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
			xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
			xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x04");
			xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
	}
}

int  create_xml_devices_sound_(xmlNodePtr grandNode,xmlNodePtr node5,xmlNodePtr childNode)
{
char *type,*name,*domain,*bus,*slot,*function;
xmlNodePtr node8=NULL;
 for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "codec")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "codec",NULL);
			  type=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "alias",NULL);
			   name=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node8, BAD_CAST "name", BAD_CAST (name));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "address",NULL);
			   type=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			   domain=xmlGetProp(grandNode,BAD_CAST "domain");
			   xmlNewProp(node8, BAD_CAST "domain", BAD_CAST (domain));
			   bus=xmlGetProp(grandNode,BAD_CAST "bus");
			   xmlNewProp(node8, BAD_CAST "bus", BAD_CAST (bus));
			   slot=xmlGetProp(grandNode,BAD_CAST "slot");
			   xmlNewProp(node8, BAD_CAST "slot", BAD_CAST (slot));
			   function=xmlGetProp(grandNode,BAD_CAST "function");
			   xmlNewProp(node8, BAD_CAST "function", BAD_CAST (function));
			   
			   
			  }  
			
			}
}

int  create_xml_devices_video(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{

int flag_video;
    flag_video=0;	
	xmlNodePtr node=NULL,node1=NULL,node2=NULL,node5=NULL,grand_node=NULL,grandNode=NULL,greatgrandNode=NULL;
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "video")==0)
                       
          {
		    flag_video=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "video",NULL); // create a child node
			create_xml_devices_video_( grandNode, node5, childNode,greatgrandNode);
		  }
	   }	
if(flag_video==0)
	{
		grand_node=xmlNewChild(child_node,NULL, BAD_CAST "video",NULL); 
		node=xmlNewChild(grand_node,NULL, BAD_CAST "model",NULL); 
		xmlNewProp(node, BAD_CAST "type", BAD_CAST "qxl");
		xmlNewProp(node, BAD_CAST "ram", BAD_CAST "65536");
		xmlNewProp(node, BAD_CAST "heads", BAD_CAST "1");
		node1=xmlNewChild(node,NULL, BAD_CAST "acceleration",NULL); 
		xmlNewProp(node1, BAD_CAST "accel3d", BAD_CAST "no");
		xmlNewProp(node1, BAD_CAST "accel2d", BAD_CAST "yes");
			
		node=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); 
		xmlNewProp(node, BAD_CAST "name", BAD_CAST "video0");
			
		node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
		xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
		xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
		xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
		xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x02");
		xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
	}	   

}
int  create_xml_devices_video_(xmlNodePtr grandNode,xmlNodePtr node5,xmlNodePtr childNode,xmlNodePtr greatgrandNode)
{
char *type9,*ram,*vram,*heads,*accel2d,*accel3d,*name,*type,*domain1,*bus,*slot,*function;
xmlNodePtr node1=NULL,node8=NULL;

for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "model")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "model",NULL);
			   type9=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type9));
			   ram=xmlGetProp(grandNode,BAD_CAST "ram");
			   xmlNewProp(node8, BAD_CAST "ram", BAD_CAST (ram));
			   vram=xmlGetProp(grandNode,BAD_CAST "vram");
			   xmlNewProp(node8, BAD_CAST "vram", BAD_CAST (vram));
			   heads=xmlGetProp(grandNode,BAD_CAST "heads");
			   xmlNewProp(node8, BAD_CAST "heads", BAD_CAST (heads));
			  for(greatgrandNode=grandNode->children;greatgrandNode;greatgrandNode=greatgrandNode->next)
			   {
			   if(xmlStrcasecmp(greatgrandNode->name,BAD_CAST "acceleration")==0)
			     {
				  node1=xmlNewChild(node8,NULL, BAD_CAST "acceleration",NULL);
				  accel3d=xmlGetProp(greatgrandNode,BAD_CAST "accel3d");
				  xmlNewProp(node1, BAD_CAST " accl3d", BAD_CAST (accel3d));
				  accel2d=xmlGetProp(greatgrandNode,BAD_CAST "accel2d");
				  xmlNewProp(node1, BAD_CAST "accel2d", BAD_CAST (accel2d));
				 }
			   }
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "alias",NULL);
			   name=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node8, BAD_CAST "name", BAD_CAST (name));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "address",NULL);
			   type=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			   domain1=xmlGetProp(grandNode,BAD_CAST "domain");
			   xmlNewProp(node8, BAD_CAST "domain", BAD_CAST (domain1));
			   bus=xmlGetProp(grandNode,BAD_CAST "bus");
			   xmlNewProp(node8, BAD_CAST "bus", BAD_CAST (bus));
			   slot=xmlGetProp(grandNode,BAD_CAST "slot");
			   xmlNewProp(node8, BAD_CAST "slot", BAD_CAST (slot));
			   function=xmlGetProp(grandNode,BAD_CAST "function");
			   xmlNewProp(node8, BAD_CAST "function", BAD_CAST (function));
			  }  
			
			}

}
 
 int  create_xml_devices_memballoon(xmlNodePtr curNode,xmlNodePtr child_node,xmlNodePtr childNode)
{
int flag_memballoon;
	flag_memballoon=0;
	char *model;
	xmlNodePtr node=NULL,node2=NULL,node5=NULL,grandNode=NULL,grand_node=NULL;	 
	for(childNode=curNode->children;childNode;childNode=childNode->next)
      { 
	 
       if(xmlStrcasecmp(childNode->name,BAD_CAST "memballoon")==0)
                       
          {
		   
		    flag_memballoon=1;
			node5=xmlNewChild(child_node,NULL, BAD_CAST "memballoon",NULL); // create a child node
			model=xmlGetProp(childNode,BAD_CAST "model");
			xmlNewProp(node5, BAD_CAST "model", BAD_CAST (model));
			create_xml_devices_memballoon_( grandNode, node5, childNode);
		  }
	   }	  
if( flag_memballoon==0)
	{
	
    grand_node=xmlNewChild(child_node,NULL, BAD_CAST "memballoon",NULL); 
	xmlNewProp(grand_node, BAD_CAST "model", BAD_CAST "virtio");
	node=xmlNewChild(grand_node,NULL, BAD_CAST "alias",NULL); 
	xmlNewProp(node, BAD_CAST "name", BAD_CAST "balloono");
		
	node2=xmlNewChild(grand_node,NULL, BAD_CAST "address",NULL); // create a child node
	xmlNewProp(node2, BAD_CAST "type", BAD_CAST "pci");
	xmlNewProp(node2, BAD_CAST "domain", BAD_CAST "0x0000");
	xmlNewProp(node2, BAD_CAST "bus", BAD_CAST "0x00");
	xmlNewProp(node2, BAD_CAST "slot", BAD_CAST "0x08");
	xmlNewProp(node2, BAD_CAST "function", BAD_CAST "0x0");
	}	   
}
int  create_xml_devices_memballoon_(xmlNodePtr grandNode,xmlNodePtr node5,xmlNodePtr childNode)
{
char *name,*type,*domain1,*bus,*slot,*function;
xmlNodePtr node8=NULL;
for(grandNode=childNode->children;grandNode;grandNode=grandNode->next)
			{
			
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "alias")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "alias",NULL);
			   name=xmlGetProp(grandNode,BAD_CAST "name");
			   xmlNewProp(node8, BAD_CAST "name", BAD_CAST (name));
			  
			  }
			if(xmlStrcasecmp(grandNode->name,BAD_CAST "address")==0)
			  {
			   node8=xmlNewChild(node5,NULL, BAD_CAST "address",NULL);
			   type=xmlGetProp(grandNode,BAD_CAST "type");
			   xmlNewProp(node8, BAD_CAST "type", BAD_CAST (type));
			   domain1=xmlGetProp(grandNode,BAD_CAST "domain");
			   xmlNewProp(node8, BAD_CAST "domain", BAD_CAST (domain1));
			   bus=xmlGetProp(grandNode,BAD_CAST "bus");
			   xmlNewProp(node8, BAD_CAST "bus", BAD_CAST (bus));
			   slot=xmlGetProp(grandNode,BAD_CAST "slot");
			   xmlNewProp(node8, BAD_CAST "slot", BAD_CAST (slot));
			   function=xmlGetProp(grandNode,BAD_CAST "function");
			   xmlNewProp(node8, BAD_CAST "function", BAD_CAST (function));
			  
			  }
			
			
			}


}

int create_xml_seclabel(xmlNodePtr root_node,xmlNodePtr proot,xmlNodePtr curNode)
{
	 int flag_seclabel;
	 flag_seclabel=0;
	 char *type;
	 xmlNodePtr node=NULL;
	 for(curNode=proot->children;curNode;curNode=curNode->next)
	{
	  if(xmlStrcasecmp(curNode->name,BAD_CAST"seclabel")==0)
	  {
	  flag_seclabel=1;
	  node=xmlNewChild(root_node,NULL, BAD_CAST "seclabel",NULL);
	  type=xmlGetProp(curNode,BAD_CAST "type");
	  xmlNewProp(node, BAD_CAST "type", BAD_CAST (type));
	
			
      }	 
	}
	if( flag_seclabel==0)
	{
	 node=xmlNewChild(root_node,NULL, BAD_CAST "seclabel",NULL);
	 xmlNewProp(node, BAD_CAST "type", BAD_CAST "none");
	}
}
  
int create_xml_qemu(xmlNodePtr root_node)
{
  xmlNodePtr child_node = NULL,grand_node=NULL, node = NULL;
  
  
   child_node=xmlNewChild(root_node,NULL, BAD_CAST "qemu:commandline",NULL);
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-tablet,id=input0");	
	
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "nec-usb-xhci,id=xhci,bus=pci.0,p2=8,p3=8,addr=0x0F");
	
    node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-chardev");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "spicevmc,name=usbredir,id=usbredirchardev1");	 
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-redir,chardev=usbredirchardev1,id=usbredirdev1,bus=xhci.0");
	
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-chardev");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "spicevmc,name=usbredir,id=usbredirchardev2");	 
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-redir,chardev=usbredirchardev2,id=usbredirdev2,bus=xhci.0");
	
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-chardev");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "spicevmc,name=usbredir,id=usbredirchardev3");	 
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-redir,chardev=usbredirchardev3,id=usbredirdev3,bus=xhci.0");
	
	
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-chardev");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "spicevmc,name=usbredir,id=usbredirchardev4");	 
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-redir,chardev=usbredirchardev4,id=usbredirdev4,bus=xhci.0");
	
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-chardev");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "spicevmc,name=usbredir,id=usbredirchardev5");	 
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-redir,chardev=usbredirchardev5,id=usbredirdev5,bus=xhci.0");
	
	
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-chardev");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "spicevmc,name=usbredir,id=usbredirchardev6");	 
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-device");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "usb-redir,chardev=usbredirchardev6,id=usbredirdev6,bus=xhci.0");
	
    node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-smbios");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "type=0,vendor=RuiJie,version=3.1.0.1");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-smbios");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "type=3,manufacturer=RuiJie,version=3.1.0.1");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-smbios");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "type=17,manufacturer=RuiJie");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "-smbios");
	node=xmlNewChild(child_node,NULL, BAD_CAST "qemu:arg",NULL);
	xmlNewProp(node, BAD_CAST "value", BAD_CAST "type=1,manufacturer=RuiJie,product=RG-RCD6000,version=3.1.0.1,family=RG-RCD,uuid=00000000-0000-0000-0000-000000000000");

}


  

int main(int argc, char *argv[])  
{

	char n=0; 
	char *importxml,*exportxml,*nodeName;
	importxml=argv[1];
	exportxml=argv[2];
	xmlChar *key,*base;
	xmlChar *value;
	xmlDocPtr doc = NULL;  
	xmlNodePtr  root_node=NULL, child_node = NULL,grand_node=NULL, node = NULL, node1 = NULL,node2=NULL,node3=NULL,node4=NULL,node5=NULL,node8=NULL;  
	xmlDocPtr doc1=NULL;
	xmlNodePtr proot=NULL, curNode=NULL,childNode=NULL, xmlChildNode=NULL,grandNode=NULL,greatgrandNode=NULL;  
	xmlKeepBlanksDefault(0); 
    
	
	
   if((access( (importxml),0))!=-1)
  {
	printf( "File importxml exists\n" );
	if(argc==3)
	{
	  printf("导入的xml文件为%s, 导出的xml文件为%s\n",importxml,exportxml);
	} 	
	else
	{
	  printf("Warning:输入的参数不对\n");		
	  return -1;
	}
  }
   else
   {
	  printf("File importxml non-existence\n ");
	  return -1;
   }
   
  
	doc1 = xmlReadFile(importxml, "UTF-8", XML_PARSE_RECOVER); // open a xml doc.
	proot = xmlDocGetRootElement(doc1); // get root element.  
	
	 if (doc1 == NULL )
   {

	 fprintf(stderr,"Document not parsed successfully. \n");
	 xmlFreeDoc (doc1);
	 return -1;

	}

	if (proot == NULL)  
	{  
	 fprintf(stderr, "open file failed. \n");  
	 xmlFreeDoc (doc1);  
	 return -1;  
	}  


	 if (xmlStrcmp(proot->name, "domain")) // if the same,xmlStrcmp return 0, else return -1  
	{  
			fprintf(stderr, "check rootElement failed. \n");  
			xmlFreeDoc (doc1);  
			return -1;  
	}

	curNode = proot->xmlChildrenNode; // move to root element's children.  
	char *content;
	xmlChar *name1,*arch,*boot,*sockets,*cores,*threads,*offset; 
	char   *mem,*currentMemory,*blkiotune,*weight,*mac, *cpu,*vcpu,*disknum,*usbredirnum,*cpumodel,*shares,*period,*quota,*qemu;
	char  *type,*machine,*domain2,*bus3,*slot2,*function2;
	
 
	doc = xmlNewDoc(BAD_CAST "1.0"); // create a new xml document.  
	root_node= xmlNewNode(NULL, BAD_CAST "domain"); // create a child node
	create_xml_domain( root_node);
	
	/*root_node= xmlNewNode(NULL, BAD_CAST "domain"); // create a child node
	xmlNewProp(root_node, BAD_CAST "type", BAD_CAST "kvm");
	xmlNewProp(root_node, BAD_CAST "id", BAD_CAST "9");
	xmlNewProp(root_node, BAD_CAST "xmlns:qemu", BAD_CAST "http://libvirt.org/schemas/domain/qemu/1.0");*/
	xmlDocSetRootElement(doc,root_node);
	
	  
	create_xml_name(root_node, proot, curNode);
	create_xml_uuid(root_node, proot, curNode);
	create_xml_memory(root_node, proot, curNode);
	create_xml_currentmemory(root_node, proot, curNode);
	create_xml_blkiotune(root_node, proot, curNode);
	create_xml_vcpu(root_node, proot, curNode,childNode);
	create_xml_cputune(root_node, proot, curNode,childNode);
	create_xml_resource(root_node, proot, curNode,childNode);
	create_xml_os(root_node, proot, curNode,childNode);
	node=xmlNewChild(root_node,NULL, BAD_CAST "features",NULL); // create a child node
	xmlNewChild(node,NULL, BAD_CAST "acpi",NULL);
	xmlNewChild(node,NULL, BAD_CAST "apic",NULL);
	xmlNewChild(node,NULL, BAD_CAST "pae",NULL);
	create_xml_cpu(root_node, proot, curNode,childNode);
	create_xml_clock(root_node, proot, curNode);
	create_xml_on_poweroff(root_node, proot, curNode);
	create_xml_on_reboot(root_node, proot, curNode);
	create_xml_on_crash(root_node, proot, curNode);
	create_xml_pm(root_node, proot, curNode,childNode);
	create_xml_devices(root_node, proot, curNode,childNode);
	create_xml_seclabel(root_node, proot, curNode);
    create_xml_qemu(root_node);
    if(argc==1 ) 
	   {   
        printf("请输入想要编辑的文件名如:./edit fillen");   
       }   
    if(argc==2)
	   {   
        printf("编辑 %sn",argv[1]);   
       }   
  

    xmlSaveFormatFileEnc(exportxml, doc, "UTF-8", 1);
    xmlFreeDoc(doc);  
    xmlFreeDoc(doc1);
    xmlFree(curNode);
    xmlCleanupParser();  
  
    xmlMemoryDump();  
    return(0);  
}  