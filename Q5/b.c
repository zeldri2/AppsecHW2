#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

static struct nf_hook_ops nfho;

unsigned int hook_func(
  void *priv,
  struct sk_buff *skb,
  const struct nf_hook_state *state
) {
  struct iphdr    * iph;
  struct udphdr   * udph;
  u16    source_port = 0;
  u16    check       = 2500;
  printk(KERN_DEBUG "hit the hook func\n"); 
  iph = ip_hdr(skb);
  if (iph) {
	iph = ip_hdr(skb);
    // Get IP header from the socket buffer
    iph = ip_hdr(skb);
    if (iph && iph->protocol == 17) {
      // Typecast udphdr pointer
      printk(KERN_DEBUG "packet is udp\n");
	    udph = (struct udphdr *)((__u32 *)iph + iph->ihl);
      if (udph) {
        // Convert the source port to integer 16bits
        source_port = ntohs(udph->source);
      }
      printk(KERN_DEBUG "source port: %d\n", source_port);
      if (source_port>check) {
        printk(KERN_DEBUG "Source port %d is higher than %d, blocking this packet", source_port, check);
        return NF_DROP;
      }
    }
  }    
  return NF_ACCEPT;
}

int init_module() {
  
  nfho.hook      = (nf_hookfn *) hook_func;
  nfho.hooknum   = NF_INET_PRE_ROUTING;
  nfho.pf        = PF_INET;
  nfho.priority  = NF_IP_PRI_FIRST;
  
  int result = nf_register_hook(&nfho);
  if (result) {
    printk(KERN_DEBUG "Firewall_lab : Error nf_register_hook !\n");
    return 1;
  }
  
  printk(KERN_DEBUG "Firewall_lab : Module charged.\n");  
  return 0;
}

void cleanup_module() {

  nf_unregister_hook(&nfho);

  printk(KERN_DEBUG "Firewall_lab : Module decharged.\n");
}