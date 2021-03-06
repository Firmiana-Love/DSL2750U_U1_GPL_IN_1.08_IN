#ifndef _LINUX_IF_SMUX_H_
#define _LINUX_IF_SMUX_H_

#include <linux/netdevice.h>
#include <linux/skbuff.h>

/* found in socket.c */
extern void smux_ioctl_set(int (*hook)(void __user *));
extern int getVidOfSmuxDev(char *name);
extern int smuxUpstreamPortmappingCheck(struct sk_buff *skb);
extern int smuxDownstreamPortmappingCheck(struct sk_buff *skb);
extern struct net_device * getSmuxDev(struct sk_buff *skb);
extern int isBrgWandevPortmappingEnable(struct net_device *dev);
extern int isSrcDevAndDstDevInSameGroup(struct net_device *src, struct net_device *dst);


/* smux device info in net_device. */
struct smux_dev_info {
	struct smux_group *smux_grp;
	struct net_device *vdev;
	struct net_device_stats stats; 
	int    proto;
	int    vid;		/* -1 means vlan disable */
	int    napt;
	unsigned int    member;	/* for port mapping */
	struct list_head  list;
};

/* represents a group of smux devices */
struct smux_group {
	struct net_device	*real_dev;
	struct list_head	smux_grp_devs;	
	struct list_head	virtual_devs;
};

#define SMUX_DEV_INFO(x) ((struct smux_dev_info *)(x->priv))

/* inline functions */

static inline struct net_device_stats *smux_dev_get_stats(struct net_device *dev)
{
  return &(SMUX_DEV_INFO(dev)->stats);
}

/* SMUX IOCTLs are found in sockios.h */

/* Passed in smux_ioctl_args structure to determine behaviour. Should be same as busybox/networking/smuxctl.c  */
enum smux_ioctl_cmds {
	ADD_SMUX_CMD,
	REM_SMUX_CMD,
};

enum smux_proto_types {
	SMUX_PROTO_PPPOE,
	SMUX_PROTO_IPOE,
	SMUX_PROTO_BRIDGE
};

/* 
 * for vlan device, smux dev name is nas0.VID, others' name is nas0_No
 */
struct smux_ioctl_args {
	int cmd; /* Should be one of the smux_ioctl_cmds enum above. */
	int proto;
	int vid; /* vid==-1 means vlan disabled on this dev. */
	int napt;
	char ifname[IFNAMSIZ];
	union {
		char ifname[IFNAMSIZ]; /* smux device info */
	} u;
};
#define rsmux_ifname	ifname
#define osmux_ifname	u.ifname
#endif /* _LINUX_IF_SMUX_H_ */
