#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/inet.h>

/* This is the structure we shall use to register our function */
static struct nf_hook_ops nfho_in; /* for incoming traffic */
static struct nf_hook_ops nfho_out; /* for outgoing traffic */

/* This is the hook function itself */
unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
	/* This is where you can inspect the packet contained in
	the structure pointed by skb, and decide whether to accept
	or drop it based on the source IP address, destination IP
	address and port numbers as required (i.e., the firewall rules).
	You can even modify the packet */

	//Incoming traffic
	

	//Outgoing traffic


	// In this example, we simply drop all packets
	return NF_DROP; /* Drop ALL packets */
	// We can alternatively accept all packets
	// return NF_ACCEPT; /* Accept ALL packets */
}

/* Initialization routine */
int init_module() {
	/* Fill in our hook structure */
	nfho_in.hook = hook_func; /* Handler function */
	nfho_in.hooknum = NF_INET_PRE_ROUTING; /* First hook for IPv4 */
	nfho_in.pf = PF_INET;
	nfho_in.priority = NF_IP_PRI_FIRST; /* Make our function first */
	nf_register_hook(&nfho_in);

	nfho_out.hook = hook_func; /* Handler function */
	nfho_out.hooknum = NF_INET_POST_ROUTING;
	nfho_out.pf = PF_INET;
	nfho_out.priority = NF_IP_PRI_FIRST; /* Make our function first */
	nf_register_hook(&nfho_out);

	return 0;
}

/* Cleanup routine */
void cleanup_module() {
	nf_unregister_hook(&nfho_in);
	nf_unregister_hook(&nfho_out);
}