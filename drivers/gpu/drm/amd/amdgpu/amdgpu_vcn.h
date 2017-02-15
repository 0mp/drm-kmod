/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __AMDGPU_VCN_H__
#define __AMDGPU_VCN_H__

#define AMDGPU_VCN_STACK_SIZE		(200*1024)
#define AMDGPU_VCN_HEAP_SIZE		(256*1024)
#define AMDGPU_VCN_SESSION_SIZE		(50*1024)
#define AMDGPU_VCN_FIRMWARE_OFFSET	256
#define AMDGPU_VCN_MAX_ENC_RINGS	3

#define VCN_DEC_CMD_FENCE		0x00000000
#define VCN_DEC_CMD_TRAP		0x00000001
#define VCN_DEC_CMD_WRITE_REG		0x00000004
#define VCN_DEC_CMD_REG_READ_COND_WAIT	0x00000006
#define VCN_DEC_CMD_PACKET_START	0x0000000a
#define VCN_DEC_CMD_PACKET_END		0x0000000b

struct amdgpu_vcn {
	struct amdgpu_bo	*vcpu_bo;
	void			*cpu_addr;
	uint64_t		gpu_addr;
	unsigned		fw_version;
	void			*saved_bo;
	struct delayed_work	idle_work;
	const struct firmware	*fw;	/* VCN firmware */
	struct amdgpu_ring	ring_dec;
	struct amdgpu_ring	ring_enc[AMDGPU_VCN_MAX_ENC_RINGS];
	struct amdgpu_irq_src	irq;
	struct amd_sched_entity entity_dec;
	struct amd_sched_entity entity_enc;
	uint32_t                srbm_soft_reset;
};

int amdgpu_vcn_sw_init(struct amdgpu_device *adev);
int amdgpu_vcn_sw_fini(struct amdgpu_device *adev);
int amdgpu_vcn_suspend(struct amdgpu_device *adev);
int amdgpu_vcn_resume(struct amdgpu_device *adev);
void amdgpu_vcn_ring_begin_use(struct amdgpu_ring *ring);
void amdgpu_vcn_ring_end_use(struct amdgpu_ring *ring);

int amdgpu_vcn_dec_ring_test_ring(struct amdgpu_ring *ring);
int amdgpu_vcn_dec_ring_test_ib(struct amdgpu_ring *ring, long timeout);

int amdgpu_vcn_enc_ring_test_ring(struct amdgpu_ring *ring);
int amdgpu_vcn_enc_ring_test_ib(struct amdgpu_ring *ring, long timeout);

#endif
