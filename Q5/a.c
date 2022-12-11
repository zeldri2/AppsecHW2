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
  struct tcphdr   * tcph;
  u16    source_port = 0;
  iph = ip_hdr(skb);
  if (iph) {
    if (iph) {
      // Typecast to either tcphdr pointer
      tcph = (struct tcphdr *)((__u32 *)iph + iph->ihl);
      if (tcph) {
        // Convert the source port to integer 16bits
        source_port = ntohs(tcph->source);
      }
      if (source_port==0x17) {
        return NF_DROP;
      }
    }
  return NF_ACCEPT;
  }
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
